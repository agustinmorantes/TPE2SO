#include "syscallHandlers.h"
#include <console.h>
#include <keyboard.h>
#include <rtc.h>
#include <scheduler.h>
#include <fd.h>
#include <pipe.h>
#include <semaphores.h>

static uint8_t rawMode = 0;

int64_t write(uint64_t fd, const char* buf, uint64_t count) {
    fd = fdLocalToGlobal(fd);
    if (fd < 0) return -1;

    if(fd == 1) {
        for(int i = 0; i < count; i++) {
            printchar(buf[i]);
        }
        return count;
    }

    if(fd == 2) {
        for(int i = 0; i < count; i++) {
            printcharc(buf[i], Black, Red);
        }
        return count;
    }

    return writefd(fd, buf ,count);
}

int64_t read(uint64_t fd, char* buf, uint64_t count) {
    fd = fdLocalToGlobal(fd);
    if (fd < 0) return -1;

    if(fd == 0) {
        if(getBackground()) {
            blockProcess(getpid());
            return 0;
        }

        //Modo raw devuelve input de teclado sin ningun procesamiento
        if(rawMode) {
            int i;
            for(i = 0; i < count; i++) {
                buf[i] = readAscii();
            }
            return i;
        }

        int i;
        for(i = 0; i < count; i++) {
            char c = readAscii();

            if(c == '\t') {
                i--;
                continue;
            }

            if(c == -1) return -1;

            //Backspace
            if(c == 8) {
                //Si llego a la pos minima no sigo borrando
                if(i <= 0) {
                    i--;
                    continue;
                }
                i-=2;
            }
            else buf[i] = c; //Escribo el caracter al buffer
        
            //Imprimo en pantalla el caracter
            printchar(c);

            //Si recibo un enter dejo de leer del teclado y devuelvo
            if(c == '\n') {
                i++;
                break;
            }
        }
    
        return i; //Devuelvo la cantidad de caracteres que leí
    }

    return readfd(fd, buf, count);
}

int64_t time(Time* res) {
    *res = getCurrentTime();
    return 0;
}

void clearTerminalSyscall() {
    clearTerminal();
}

void setTerminalRawMode(uint8_t setRaw) {
    rawMode = setRaw != 0;
}

void printmem(const void* ptr) {
    //Casteo el puntero como puntero a uint8_t
    //para printearlo byte por byte
    const uint8_t* aux = (const uint8_t*)ptr;

    //Pure64 carga la cantidad de ram en 0x5020
    const uint32_t ramMb = *(uint32_t*)0x5020;
    uint64_t maxDir = ramMb * 1024 * 1024 - 1;

    if((uint64_t)ptr > maxDir) {
        print("Invalid memory address");
        newLine();
        print("Max dir: 0x");
        printhex(maxDir);
        newLine();
        print("Ram amount: ");
        printnum(ramMb);
        print("MB");
        newLine();
        return;
    }

    //Recorro los primeros 32bytes y los muestro en pantalla
    for(int i = 0; i < 32; i++) {
        printhex((uint64_t)aux[i]);
        printchar(' ');
    }
}

void exitSyscall() {
    terminateProcess(getpid());
}

PID getPidSyscall() {
    return getpid();
}

int64_t kill(PID pid) {
    return terminateProcess(pid);
}

int64_t changePrioritySyscall(PID pid, Priority priority) {
    return changePriority(pid, priority);
}

int64_t blockProcessSyscall(PID pid) {
    return blockProcess(pid);
}

int64_t unblockProcessSyscall(PID pid) {
    return unblockProcess(pid);
}

void yieldSyscall(void) {
    yield();
}

int setBackgroundSyscall(PID pid, Background background) {
    return setBackground(pid, background);
}

int64_t pipeSyscall(uint64_t fd[2]) {
    int result = openPipe(fd);
    if (result >= 0) {
        addFd(fd[0]);
        addFd(fd[1]);
    }
    return result;
}

int64_t close(uint64_t fd) {
    fd = fdLocalToGlobal(fd);
    int result = closefd(fd);
    if (result >= 0)
        removeFd(fd);
    return result;
}

int64_t mkfifoSyscall(uint64_t id) {
    return mkfifo(id);
}

int64_t openFifoSyscall(uint64_t id, fdType type) {
    int64_t fd = openFifo(id, type);
    if (fd >= 0) addFd(fd);
    return fd;
}

int mapStdFdsSyscall(PID pid, int stdin, int stdout) {
    return mapStdFds(pid, stdin, stdout);
}

int64_t rmFifoSyscall(uint64_t id) {
    return rmFifo(id);
}

void listPipesSyscall() {
    listPipes();
}

int semOpenSyscall(semID id, uint64_t value) {
    return semOpen(id, value);
}

int semWaitSyscall(semID id) {
    return semWait(id);
}

int semPostSyscall(semID id) {
    return semPost(id);
}

int semCloseSyscall(semID id) {
    return semClose(id);
}

void listProcessSyscall() {
    listProcesses();
}

void listSemaphoreSyscall() {
    semPrintAll();
}