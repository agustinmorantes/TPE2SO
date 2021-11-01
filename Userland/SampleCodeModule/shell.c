#include <shell.h>
#include <io.h>
#include <str.h>
#include <commands.h>
#include <syscall.h>

#define NULL 0
#define MAX_CMD_LEN 1024

#define FOREGROUND_SEM 0
#define START_PROC_SEM 1

static const Command parseCommand(int argc, const char** argv) {
	for(int i = 0; i < CMD_COUNT; i++) {
		if(strcmp(argv[0],commands[i].name) != 0) continue;

		Command c = commands[i];
		c.isBackground = argv[argc-1][0] == '&';
		return c; 
	}

	Command c = {NULL,NULL,0};
	return c;
}

static uint8_t split(char* input, char* buf[], uint8_t maxCount) {
	char c;
	int word = 0;
	buf[word] = input;
	while((c = *input++) != 0 && word < maxCount-1) {
		if(c != ' ') continue;

		*(input-1) = 0;
		buf[++word] = input;
	}

	return word+1;
}

int readinput(char* outputBuf) {
	printf("> ");
	int len = _sysread(0, outputBuf, MAX_CMD_LEN);
	if(len <= 0) return -1;
	outputBuf[len-1] = 0;
}

int shellProcessWrapper(int argc, char** argv) {
	_semopen(FOREGROUND_SEM, 0);
	_semopen(START_PROC_SEM, 0);
	_semwait(START_PROC_SEM);
	
	Background bg = (int)argv[argc+1];
	CmdHandler cmd = (CmdHandler)argv[argc];

	int pipeFdToClose = (int)argv[argc+2];
	if(pipeFdToClose >= 0) {
		_sysclose(pipeFdToClose);
	}
	
	PID pid = _sysgetpid();
    
	int retcode = cmd(argc-bg, argv);
	_sysmapstdfds(pid, 0, 1);
	if(!bg) _sempost(FOREGROUND_SEM);

	_semclose(FOREGROUND_SEM);
	_semclose(START_PROC_SEM);
    _sysexit();
}

int checkPipeCommand(int* argc0, char** argv0, char** argv1) {
	int totalArgs = *argc0;
	for(int i = 0; i < totalArgs; i++) {
		if(strcmp(argv0[i],"|") == 0) {
			*argc0 = i;

			for(int j = i+1; j < totalArgs; j++) {
				argv1[j-i-1] = argv0[j];
			}

			return 1;
		}
	}
	return 0;
}

void runShell() {
	_semopen(FOREGROUND_SEM, 0);
	_semopen(START_PROC_SEM, 0);

    while(1) {
		char input[MAX_CMD_LEN];

		if(readinput(input) < 0){
			printf("\n");
			continue;
		}

		if(strcmp(input, "") == 0)
			continue;

		char* argv0[64];
		int totalArgc = split(input, argv0, 64);

		int argc0 = totalArgc;
		char* argv1[64];
		int pipeCommand = checkPipeCommand(&argc0, argv0, argv1);

		if(pipeCommand) {
			int argc1 = totalArgc-argc0-1;
			Command cmd0 = parseCommand(argc0, argv0);
			Command cmd1 = parseCommand(argc1, argv1);

			if(cmd0.handler == NULL || cmd1.handler == NULL) {
				printf("[SHELL] Error: command not found\n");
				continue;
			}

			uint64_t pipe[2];
			if(_syspipe(pipe) < 0) {
				printf("[SHELL] Error: pipe failed\n");
				continue;
			}

			argv0[argc0] = (char*)cmd0.handler;
			argv0[argc0+2] = (char*)pipe[0];
			argv1[argc1] = (char*)cmd1.handler;
			
			argv1[argc1+2] = (char*)pipe[1];
			PID pid0 = _syscreateprocess(&shellProcessWrapper, argc0, argv0);
			PID pid1 = _syscreateprocess(&shellProcessWrapper, argc1, argv1);
			_sysmapstdfds(pid0, STDIN, pipe[1]);
			_sysmapstdfds(pid1, pipe[0], STDOUT);
			_sysclose(pipe[0]);
			_sysclose(pipe[1]);

			if(cmd1.isBackground) {
				argv0[argc0+1] = (char*)BACKGROUND;
				argv1[argc1+1] = (char*)BACKGROUND;
				_syschgpriority(pid0, 1);
				_syschgpriority(pid1, 1);
				_sempost(START_PROC_SEM);
				_sempost(START_PROC_SEM);
			}
			else {
				argv0[argc0+1] = (char*)FOREGROUND;
				argv1[argc1+1] = (char*)FOREGROUND;
				_syssetbackground(pid0, FOREGROUND);
				_sempost(START_PROC_SEM);
				_sempost(START_PROC_SEM);
				_semwait(FOREGROUND_SEM);
				_semwait(FOREGROUND_SEM);
			}
			continue;
		}
		
		Command cmd = parseCommand(totalArgc,argv0);
		if(cmd.handler == NULL) {
			printf("Comando desconocido: %s\n", argv0[0]);
			continue;
		}

		argv0[totalArgc] = (char*)cmd.handler;
		argv0[totalArgc+2] = (char*)-1;
		if(cmd.isBackground) {
			argv0[totalArgc+1] = (char*)BACKGROUND;
			PID pid = _syscreateprocess(&shellProcessWrapper, totalArgc, argv0);
			_syschgpriority(pid, 1);
			_sempost(START_PROC_SEM);
		} else {
			argv0[totalArgc+1] = (char*)FOREGROUND;
			PID pid = _syscreateprocess(&shellProcessWrapper, totalArgc, argv0);
			_syssetbackground(pid, FOREGROUND);
			_sempost(START_PROC_SEM);
			_semwait(FOREGROUND_SEM);
		}
    }

	_semclose(FOREGROUND_SEM);
	_semclose(START_PROC_SEM);
}
