#include <shell.h>
#include <io.h>
#include <str.h>
#include <commands.h>
#include <syscall.h>

#define NULL 0
#define MAX_CMD_LEN 1024

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
	Background bg = (int)argv[argc+1];
	CmdHandler cmd = (CmdHandler)argv[argc];

	PID pid = _sysgetpid();
    
	if(bg) printf("[SHELL] Proceso con PID %d\n", pid);
    
	int retcode = cmd(argc-bg, argv);
	_sysmapstdfds(pid, 0, 1);
    //printf("[SHELL] Process exit code: %d", retcode);
	_sempost(SHELL_SEM);
    _sysexit();
}

void runShell() {
	_semopen(SHELL_SEM, 0);

    while(1) {
		char input[MAX_CMD_LEN];

		if(readinput(input) < 0){
			printf("\n");
			continue;
		}

		if(strcmp(input, "") == 0)
			continue;

		char* argv[64];
		int argc = split(input, argv, 64);

		Command cmd = parseCommand(argc,argv);
		if(cmd.handler == NULL) {
			printf("Comando desconocido: %s\n", argv[0]);
			continue;
		}

		if(cmd.isBackground) {
			argv[argc] = (char*)cmd.handler;
			argv[argc+1] = (char*)BACKGROUND;
			PID pid = _syscreateprocess(&shellProcessWrapper, argc, argv);
			_syschgpriority(pid, 1);
		} else {
			argv[argc] = (char*)cmd.handler;
			argv[argc+1] = (char*)FOREGROUND;
			PID pid = _syscreateprocess(&shellProcessWrapper, argc, argv);
			_syssetbackground(pid, FOREGROUND);
			_semwait(SHELL_SEM);
		}
    }

	_semclose(SHELL_SEM);
}
