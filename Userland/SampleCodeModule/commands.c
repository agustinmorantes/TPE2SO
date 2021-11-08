#include <commands.h>
#include <io.h>
#include <stdint.h>
#include <currentTime.h>
#include <syscall.h>
#include <inforeg.h>
#include <str.h>
#include <cpufeatures.h>

int cmd_help() {
    printf("Lista de comandos:\n");
    for(int i = 0; i < CMD_COUNT; i++) {
        if(i%6 == 0) printf("\n");
        
        if(i == CMD_COUNT-1) {
            printf("%s\n",commands[i].name);
        } else printf("%s | ",commands[i].name);

    }
    return 0;
}

int cmd_clear() {
    clearTerminal();
    return 0;
}

int cmd_greet() {
	printf("Ingrese su nombre: ");

	char input[128];
	scanf("%s", input);

	printf("Hola %s!\n", input);
	return 0;
}

int cmd_time() {
	printCurrentTime();
    printf("\n");
	return 0;
}

int cmd_printmem(int argc, const char* argv[]) {
    if(argc < 2) {
        printf("USO: printmem [MEM POINTER]\n");
        return -1;
    }

    int dir = -1;
    strToIntBase(argv[1], strlen(argv[1]), 16, &dir,1);

    if (dir == -1) {
        printf("USO: printmem [MEM POINTER]\n");
        return -1;
    }
    
    _sysprintmem((const void*)(uint64_t)dir);
    printf("\n");
    return 0;
}

int cmd_inforeg() {
    inforeg();
    return 0;
}

int cmd_printcpufeatures() {
    printcpufeatures();
    return 0;
}

int cmd_divbyzero() {
    int a = 1/0;
    return a;
}

void _invalidopcode();

int cmd_invalidopcode() {
    _invalidopcode();
    return 0;
}

int _getRoots(double a, double b, double c, double * root1, double * root2);

int cmd_roots() {
    double a = 0,b = 0,c = 0;
    printf("Inserte los parametros de la cuadratica (a, b, c): ");
    scanf("%f %f %f",&a,&b,&c);
    double root1, root2;

    if (a == 0)
    {
        printf("Input invalido, lo insertado no es una cuadratica\n");
        return -1;
    }
    
    int result = _getRoots(a,b,c,&root1,&root2);

    if (result) {
        printf("Las raices son: %f y %f\n", root1, root2);
        return 0;
    }

    printf("La ecuacion no tiene raices reales\n");
    return -1;
}

int cmd_suma() {
    int a,b;
    printf("Inserte numeros a sumar: ");
    scanf("%d %d",&a,&b);
    printf("El resultado es: %d\n", a + b);
    return 0;
}

int cmd_loop() {
    Time t = getCurrentTime();
    PID pid = _sysgetpid();
    while(1) {
        Time newT = getCurrentTime();
        if((t.seconds != newT.seconds) && (newT.seconds % 3 == 0)) {
            t = newT;
            printf("[PID:%d] Hola soy loop\n", pid);
        }
        _sysyield();
    }
}

int cmd_fdMap_test() {
    PID pid = _sysgetpid();
    _sysmapstdfds(pid, -1, -1);
    printf("Esto no debería printearse");
    _sysmapstdfds(pid, 0, 1);
    return 1;
}

int cmd_kill(int argc, const char** argv) {
    if (argc < 2) {
        printf("USE: kill [PID]\n");
        return -1;
    }

    int pid = -1;
    strToIntBase(argv[1], strlen(argv[1]), 10, &pid, 1);

    if (pid == -1) {
        printf("USO: kill [PID]\n");
        return -1;
    }

    if(_syskill(pid) < 0) {
        printf("Couldn't kill process with PID %d\n", pid);
        return -1;
    }

    return 0;
}

int cmd_nice(int argc, const char** argv) {
    if (argc < 2) {
        printf("USE: nice [PID]\n");
        return -1;
    }

    int pid = -1;
    Priority priority = -1;
    strToIntBase(argv[1], strlen(argv[1]), 10, &pid, 1);
    strToIntBase(argv[2], strlen(argv[2]), 10, (int*)&priority, 1);

    if (pid == -1) {
        printf("USE: nice [PID] [PRIORITY(1-3)]\n");
        return -1;
    }

    if(priority < 1 || priority > 3) {
        printf("Invalid priority. USE: nice [PID] [PRIORITY(1-3)]\n");
        return -1;
    }

    if(_syschgpriority(pid, priority) < 0) {
        printf("Couldn't change priority of process with PID %d\n", pid);
        return -1;
    }

    return 0;
}

int cmd_block(int argc, const char** argv) {
    if (argc < 2) {
        printf("USE: block [PID]\n");
        return -1;
    }

    int pid = -1;
    strToIntBase(argv[1], strlen(argv[1]), 10, &pid, 1);

    if (pid == -1) {
        printf("USE: block [PID]\n");
        return -1;
    }

    if(_sysblock(pid) < 0 && _sysunblock(pid) < 0) {
        printf("Couldn't block/unblock process with PID %d\n", pid);
        return -1;
    }

    return 0;
}

int cmd_cat() {
    char buffer[1024];
    int bytesRead = 0;
    while((bytesRead = _sysread(STDIN, buffer, 1024)) > 0) {
        _syswrite(1, buffer, bytesRead);
    }

    return 0;
}

int cmd_wc() {
    char buffer[1024];
    int bytesRead = 0;
    int lines = 1;
    int wasLastCharNewline = 0;
    while((bytesRead = _sysread(STDIN, buffer, 1024)) > 0) {
        for(int i = 0; i < bytesRead; i++) {
            wasLastCharNewline = 0;
            if(buffer[i] == '\n') {
                lines++;
                wasLastCharNewline = 1;
            }
        }
    }

    if(wasLastCharNewline) lines--;

    printf("\nLines: %d\n", lines);
    return 0;
}

int cmd_filter() {
    char buffer[1024];
    int bytesRead = 0;
    while((bytesRead = _sysread(STDIN, buffer, 1024)) > 0) {
        for(int i = 0; i < bytesRead; i++) {
            if( buffer[i] == 'a' ||
                buffer[i] == 'e' ||
                buffer[i] == 'i' ||
                buffer[i] == 'o' ||
                buffer[i] == 'u') continue;
                
            _syswrite(1, &buffer[i], 1);
        }
    }

    return 0;
}

int cmd_ps() {
    _syslistprocesses();
    return 0;
}

int cmd_pipe() {
    _syslistpipes();
    return 0;
}

int cmd_sem() {
    _syslistsem();
    return 0;
}

int cmd_not_implemented() {
    printf("Comando no implementado\n");
    return 0;
}

#define SHM_ID 1

int cmd_shm_write() {
    void* shm = createSharedMemory(SHM_ID);
    if(shm == NULL) {
        printf("ERROR AL CREAR SHM");
        return 1;
    }

    char* ptr = (char*) shm;
    *ptr = 0;

    Time t = getCurrentTime();
    PID pid = _sysgetpid();
    while(1) {
        Time newT = getCurrentTime();
        if((t.seconds != newT.seconds) && (newT.seconds % 3 == 0)) {
            t = newT;
            *ptr = '1';
            ptr++;
            *ptr = 0;
            ptr++;
        }
        _sysyield();
    }
}

int cmd_shm_read() {
    void* shm = createSharedMemory(SHM_ID);
    if(shm == NULL) {
        printf("ERROR AL CREAR SHM");
        return 1;
    }

    char* ptr = (char*)shm;

    while(1) {
        if(*ptr != 0) {
            printf("%c", *ptr);
            ptr++;
        }
        _sysyield();
    }
}
