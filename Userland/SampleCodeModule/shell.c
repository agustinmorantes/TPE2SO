#include <shell.h>
#include <io.h>
#include <str.h>
#include <commands.h>
#include <syscall.h>

#define NULL 0
#define MAX_CMD_LEN 1024

#define START_PROC_SEM 1

#define WRAPPER_ARGS 4

static PID shellPid;

static uint8_t isForeground = 1;

static void setShellBackground() {
	_syssetbackground(shellPid, BACKGROUND);
	isForeground = 0;
}

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
	if(isForeground) printf("> ");
	int len = 0;
	len = _sysread(0, outputBuf, MAX_CMD_LEN);
	if(len <= 0) {
		if(!isForeground) printf("> ");
		return -1;
	}
	isForeground = 1;
	outputBuf[len-1] = 0;
	return 0;
}

int shellProcessWrapper(int argc, char** argv) {
	_semopen(START_PROC_SEM, 0);
	_semwait(START_PROC_SEM);
	
	Background bg;
	strToIntBase(argv[argc-WRAPPER_ARGS+1], strlen(argv[argc-WRAPPER_ARGS+1]), 10, (int*)&bg, 1);

	uint64_t cmdInt;
	strToIntBase(argv[argc-WRAPPER_ARGS], strlen(argv[argc-WRAPPER_ARGS]), 10, (int*)&cmdInt, 1);
	
	CmdHandler cmd = (CmdHandler)cmdInt;

	int unusedPipeEnd;
	strToIntBase(argv[argc-WRAPPER_ARGS+2], strlen(argv[argc-WRAPPER_ARGS+2]), 10, &unusedPipeEnd, 0);

	int usedPipeEnd;
	strToIntBase(argv[argc-WRAPPER_ARGS+3], strlen(argv[argc-WRAPPER_ARGS+3]), 10, &usedPipeEnd, 0);

	if(unusedPipeEnd >= 0) {
		_sysclose(unusedPipeEnd);
	}
	
	PID pid = _sysgetpid();
    
	int retcode = cmd(argc-WRAPPER_ARGS, (const char**)argv);
	_sysmapstdfds(pid, 0, 1);

	if(usedPipeEnd >= 0)
		_sysclose(usedPipeEnd);

	_semclose(START_PROC_SEM);
    _sysexit();
	return retcode;
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

void runCommand(Command cmd, int argc, char** argv) {
	char handlerStr[24];
	uintToBase((uint64_t)cmd.handler, handlerStr, 10);
	
	argv[argc] = handlerStr;
	argv[argc+2] = "-1";
	argv[argc+3] = "-1";

	if(cmd.isBackground) {
		argv[argc+1] = "1"; //Background

		PID pid = _syscreateprocess(&shellProcessWrapper, argc+WRAPPER_ARGS, argv);
		_syschgpriority(pid, 1);
		_sempost(START_PROC_SEM);
	} else {
		argv[argc+1] = "0"; //Foreground

		PID pid = _syscreateprocess(&shellProcessWrapper, argc+WRAPPER_ARGS, argv);
		setShellBackground();
		_syssetbackground(pid, FOREGROUND);
		_sempost(START_PROC_SEM);
	}
}

void runPipedCommands(Command cmd0, Command cmd1, int argc0, int argc1, char** argv0, char** argv1) {
	uint64_t pipe[2];
	if(_syspipe(pipe) < 0) {
		printf("[SHELL] Error: pipe failed\n");
		return;
	}

	char handler0Str[24]; char handler1Str[24];
	uintToBase((uint64_t)cmd0.handler, handler0Str, 10);
	uintToBase((uint64_t)cmd1.handler, handler1Str, 10);

	char pipeOutStr[24]; char pipeInStr[24];
	uintToBase(pipe[1], pipeOutStr, 10);
	uintToBase(pipe[0], pipeInStr, 10);

	argv0[argc0] = handler0Str;
	argv1[argc1] = handler1Str;
	
	//Pipes to close
	argv0[argc0+2] = pipeInStr;
	argv0[argc0+3] = pipeOutStr;

	argv1[argc1+2] = pipeOutStr;
	argv1[argc1+3] = pipeInStr;

	if(cmd1.isBackground) {
		argv0[argc0+1] = "1";
		argv1[argc1+1] = "1";
	} 
	else {
		argv0[argc0+1] = "0";
		argv1[argc1+1] = "0";
	}

	PID pid0 = _syscreateprocess(&shellProcessWrapper, argc0+WRAPPER_ARGS, argv0);
	PID pid1 = _syscreateprocess(&shellProcessWrapper, argc1+WRAPPER_ARGS, argv1);
	_sysmapstdfds(pid0, STDIN, pipe[1]);
	_sysmapstdfds(pid1, pipe[0], STDOUT);
	_sysclose(pipe[0]);
	_sysclose(pipe[1]);

	if(cmd1.isBackground) {
		_syschgpriority(pid0, 1);
		_syschgpriority(pid1, 1);
		_sempost(START_PROC_SEM);
		_sempost(START_PROC_SEM);
	}
	else {
		setShellBackground();
		_syssetbackground(pid0, FOREGROUND);
		_sempost(START_PROC_SEM);
		_sempost(START_PROC_SEM);
	}
}

void runShell() {
	_semopen(START_PROC_SEM, 0);

	shellPid = _sysgetpid();

    while(1) {
		char input[MAX_CMD_LEN];

		if(readinput(input) < 0)
			continue;

		if(strcmp(input, "") == 0)
			continue;

		char* argv0[64];
		int totalArgc = split(input, argv0, 64);

		int argc0 = totalArgc;
		char* argv1[64];
		int pipeCommand = checkPipeCommand(&argc0, argv0, argv1);

		if(pipeCommand) {
			int argc1 = totalArgc-argc0-1;
			Command cmd0 = parseCommand(argc0, (const char**)argv0);
			Command cmd1 = parseCommand(argc1, (const char**)argv1);

			if(cmd0.handler == NULL || cmd1.handler == NULL) {
				printf("[SHELL] Error: command not found\n");
				continue;
			}

			runPipedCommands(cmd0, cmd1, argc0, argc1, argv0, argv1);
			continue;
		}
		
		Command cmd = parseCommand(totalArgc,(const char**)argv0);
		if(cmd.handler == NULL) {
			printf("Comando desconocido: %s\n", argv0[0]);
			continue;
		}

		runCommand(cmd, totalArgc, argv0);
    }

	_semclose(START_PROC_SEM);
}
