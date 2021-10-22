#include <shell.h>

int main(int argc, const char* argv[]) {
	printf("argc: %d\n", argc);
	
	printf("argv:");
	for(int i = 0; i < argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");

	runShell();
	return 0;
}