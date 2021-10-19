#include <shell.h>
#include <io.h>
#include <str.h>
#include <commands.h>
#include <syscall.h>

#define NULL 0
#define MAX_CMD_LEN 1024

static const Command* parseCommand(const char* input) {
	for(int i = 0; i < CMD_COUNT; i++) {
		if(strcmp(input,commands[i].name) == 0) return &commands[i];
	}

	return 0;
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

		const Command* cmd = parseCommand(argv[0]);
		if(cmd != 0) {
			cmd->handler(argc, (const char**)argv);
		}
		else {
			printf("Comando desconocido.\n");
		}
    }
}
