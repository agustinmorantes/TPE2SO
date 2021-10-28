#include "syscallHandlers.h"
#include <console.h>
#include <keyboard.h>
#include <rtc.h>
#include <scheduler.h>
#include <fd.h>
#include <pipe.h>

static uint8_t rawMode = 0;

int64_t write(uint64_t fd, const char* buf, uint64_t count) {
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

void exit() {
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
    setBackground(pid, background);
}

int64_t pipeSyscall(uint64_t fd[2]) {
    return openPipe(fd);
}

int64_t close(uint64_t fd) {
    return closefd(fd);
}

int64_t mkfifoSyscall(uint64_t id) {
    return mkfifo(id);
}

int64_t openFifoSyscall(uint64_t id, fdType type) {
    return openFifo(id, type);
}



