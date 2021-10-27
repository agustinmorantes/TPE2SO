#include <commands.h>
#include <io.h>
#include <stdint.h>
#include <currentTime.h>
#include <syscall.h>
#include <inforeg.h>
#include <str.h>
#include <cpufeatures.h>

int cmd_lscmd() {
    printf("Lista de comandos:\n");
    for(int i = 0; i < CMD_COUNT; i++) {
        printf("%s\n",commands[i].name);
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

int cmd_background_test() {
    Time t = getCurrentTime();
    while(1) {
        if(t.seconds != (t = getCurrentTime()).seconds && t.seconds % 3 == 0) {
            printCurrentTime();
            printf("\n");
        }
    }
}

int cmd_fdMap_test() {
    PID pid = _sysgetpid();
    _sysmapstdfds(pid, -1, -1);
    printf("Esto no debería printearse");
    _sysmapstdfds(pid, 0, 1);
    return 1;
}