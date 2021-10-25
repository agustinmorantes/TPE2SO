#include <shell.h>
#include <io.h>
#include <str.h>
#include <commands.h>
#include <syscall.h>

#define NULL 0
#define MAX_CMD_LEN 1024

int shellProcessWrapper(int argc, char** argv);

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

void readinput(char* outputBuf) {
	printf("> ");
	int len = _sysread(0, outputBuf, MAX_CMD_LEN);
	outputBuf[len-1] = 0;
}

void runShell() {
    while(1) {
		char input[MAX_CMD_LEN];
		readinput(input);

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
			PID pid = _syscreateprocess(&shellProcessWrapper, argc, argv);
			_syschgpriority(pid, 1);
		} else {
			cmd.handler(argc, argv);
		}
    }
}
