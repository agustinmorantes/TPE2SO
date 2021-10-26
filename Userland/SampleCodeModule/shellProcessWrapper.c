#include <syscall.h>
#include <commands.h>

int shellProcessWrapper(int argc, char** argv) {
    printf("[SHELL] Proceso Background con PID %d\n", _sysgetpid());
    int retcode = ((CmdHandler)argv[argc])(argc-1, argv);
    printf("[SHELL] Process exit code: %d", retcode);
    _sysexit();
}
