#include <shell.h>
#include <io.h>
#include <str.h>
#include <commands.h>
#include <syscall.h>

#define NULL 0
#define TERMINAL_COUNT 1
#define MAX_CMD_LEN 1024

// atributos para gcc, porque por default se guarda en bss el cual se limpia al reiniciar el shell
static char buffers[TERMINAL_COUNT][MAX_CMD_LEN] __attribute__ ((section ("data")));
static int64_t bufferPos[TERMINAL_COUNT] __attribute__ ((section ("data")));
static uint8_t notinitialized = 1;

static const Command* parseCommand(const char* input) {
	for(int i = 0; i < CMD_COUNT; i++) {
		if(strcmp(input,commands[i].name) == 0) return &commands[i];
	}

	return 0;
}

static void switchTerminal(){
	_sysswitchterminal();
}

static unsigned int readinput(char* outputBuf) {
	_systerminalraw(1);
	uint64_t currentTerminal = _sysgetcurrentterminal();

	while(bufferPos[currentTerminal] < MAX_CMD_LEN) {
		if(bufferPos[currentTerminal] == -1) {
			printf(">");
			bufferPos[currentTerminal] = 0;
		}

		char c;
		_sysread(0, &c, 1);

		if(c == '\n') {
			printf("\n");
			break;
		}
		if(c == '\t') {
			switchTerminal();
			currentTerminal = _sysgetcurrentterminal();
			continue;
		}
		if(c == 8) { //Backspace
			if(bufferPos[currentTerminal] > 0) {
				printf("%c",c);
				bufferPos[currentTerminal]--;
			}
			continue;
		}

		printf("%c",c);
		buffers[currentTerminal][bufferPos[currentTerminal]] = c;
		bufferPos[currentTerminal]++;
	}

	_systerminalraw(0);

	//Copio el buffer y lo limpio
	int i;
    for(i = 0; i < bufferPos[currentTerminal]; i++) {
		outputBuf[i] = buffers[currentTerminal][i];
	}
	outputBuf[i] = 0;
	bufferPos[currentTerminal] = -1;

    return i;
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

void runShell() {
	//Inicializo los buffers
	if (notinitialized)
	{
		for(int i = 0; i < TERMINAL_COUNT; i++) {
			bufferPos[i] = -1;
		} 
	}
	notinitialized = 0;

	bufferPos[_sysgetcurrentterminal()] = -1;

    while(1) {
		char input[MAX_CMD_LEN];
		readinput(input);

		char* argv[64];
		int argc = split(input, argv, 64);

		const Command* cmd = parseCommand(argv[0]);
		if(cmd != 0) {
			cmd->handler(argc, (const char**)argv);
		}
		else {
			printf("Comando desconocido.\n\n");
			parseCommand("lscmd")->handler(0, NULL);
		}
    }
}
