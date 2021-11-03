#include <stdlib.h>
#include <stdint.h>
#include <fd.h>
#include <pipe.h>
#include <memory_manager.h>
#include <scheduler.h>
#include <console.h>
#include <semaphores.h>

#define PIPE_BUF 4096
#define MAX_FIFO 64

static int semcounter = 0;
struct Pipe {
    char buf[PIPE_BUF];
    uint32_t readIdx;
    uint32_t writeIdx;
    int readOpen;
    int writeOpen;
    int readpid;
    int writepid;
    semID writequeue;
    semID readqueue;

    // only for printing
    int readfd;
    int writefd;
};

typedef struct fifo {
    uint64_t id;
    uint64_t readfd;
    uint64_t writefd;
} FIFO;

static FIFO fifoTable[MAX_FIFO];

// only for printing
static PIPE pipeTable[MAX_FD];

int64_t mkfifo(uint64_t id) {
    if (id == 0) return -1; // 0 not a valid id
    int64_t k = -1;
    for (int64_t i = 0; i < MAX_FIFO; i++) {
        if (fifoTable[i].id == id) // ya existe
            return -1;
        if (fifoTable[i].id == 0 && k == -1) // encontre lugar
            k = i;
    }

    if (k >= 0) {
        uint64_t fd[2];
        if (openPipe(fd) < 0)
            return -1;
        fifoTable[k].id = id;
        fifoTable[k].readfd = fd[0];
        fifoTable[k].writefd = fd[1];
        return 0;
    }
    return -1;
}

int64_t openFifo(uint64_t id, fdType type) {
    if (id == 0) return -1; // 0 not a valid id
    for (int64_t i = 0; i < MAX_FIFO; i++) {
        if (fifoTable[i].id == id) {
            if (type == READ) {
                fddup(fifoTable[i].readfd);
                return fifoTable[i].readfd;
            }
            if (type == WRITE) {
                fddup(fifoTable[i].writefd);
                return fifoTable[i].writefd;
            }
        }
    }
    return -1;
}

int64_t rmFifo(uint64_t id) {
    if (id == 0) return -1; // 0 not a valid id
    for (int64_t i = 0; i < MAX_FIFO; i++) {
        if (fifoTable[i].id == id) {
            fifoTable[i].id = 0;
            closefd(fifoTable[i].readfd);
            closefd(fifoTable[i].writefd);
            fifoTable[i].readfd = 0;
            fifoTable[i].writefd = 0;
            return 0;
        }
    }
    return -1;
}

int64_t openPipe(uint64_t fd[2]) {
    PIPE pipe = alloc(sizeof(struct Pipe));
    if (pipe == NULL)
        return -1;

    int64_t id;

    id = initfd(READ, pipe);
    if (id < 0)  {
        free(pipe);
        return -1;
    }
    fd[0] = id;
    
    id = initfd(WRITE, pipe);
    if (id < 0)  {
        free(pipe);
        return -1;
    }
    fd[1] = id;

    pipe->writeOpen = 1;
    pipe->readOpen = 1;
    pipe->readIdx = 0;
    pipe->writeIdx = 0;

    pipe->writequeue = semcounter++;
    pipe->readqueue = semcounter++;

    semOpen(pipe->writequeue, 1);
    semOpen(pipe->readqueue, 1);
    
    // only for printing
    pipe->readfd = fd[0];
    pipe->writefd = fd[1];
    for (size_t i = 0; i < MAX_FD; i++) {
        if (pipeTable[i] == NULL) {
            pipeTable[i] = pipe;
            break;
        }
    }
    
    return 0;
}

void closePipe(PIPE pipe, fdType type) {
    if (type == READ)
        pipe->readOpen = 0;
    else if (type == WRITE) {
        pipe->writeOpen = 0;
        pipe->buf[pipe->writeIdx++ % PIPE_BUF] = -1;
    }
    
    if (!pipe->readOpen && !pipe->writeOpen) {
        // only for printing
        for (size_t i = 0; i < MAX_FD; i++) {
            if (pipeTable[i] == pipe) {
                pipeTable[i] = NULL;
                break;
            }
        }
        deleteSemaphore(pipe->readqueue);
        deleteSemaphore(pipe->writequeue);
        free(pipe);
    }
}

int64_t readPipe(PIPE pipe, char* buf, uint64_t count) {
    if (!pipe->readOpen)
        return -1;

    semWait(pipe->readqueue);

    pipe->readpid = getpid();
    while (pipe->readIdx == pipe->writeIdx) {
        if (!pipe->writeOpen) {
            pipe->readpid = 0;
            semPost(pipe->readqueue);
            return 0;
        }
        blockProcess(pipe->readpid);
    }
    pipe->readpid = 0;

    int i;
    for(i = 0; i < count; i++) {
        if(pipe->readIdx == pipe->writeIdx)
            break;
        if(pipe->buf[pipe->readIdx % PIPE_BUF] == -1)
            break;
        buf[i] = pipe->buf[pipe->readIdx++ % PIPE_BUF];
    }

    if (pipe->writepid)
        unblockProcess(pipe->writepid);

    semPost(pipe->readqueue);
    return i;
}

int64_t writePipe(PIPE pipe, const char* buf, uint64_t count) {
    if (!pipe->writeOpen || !pipe->readOpen)
        return -1;

    semWait(pipe->writequeue);

    for(int i = 0; i < count; i++) {
        pipe->writepid = getpid();
        while(pipe->writeIdx == pipe->readIdx + PIPE_BUF) {
            if(!pipe->readOpen) {
                pipe->writepid = 0;
                semPost(pipe->writequeue);
                return -1;
            }
            if (pipe->readpid) 
                unblockProcess(pipe->readpid);
            blockProcess(pipe->writepid);
        }
        pipe->writepid = 0;
        pipe->buf[pipe->writeIdx++ % PIPE_BUF] = buf[i];
    }

    if (pipe->readpid) 
        unblockProcess(pipe->readpid);

    semPost(pipe->writequeue);
    return count;
}

void listPipes() {
    println("Lista de pipes del sistema:");
    println("readfd | writefd | bytesToRead | readPid | writePid | writeQueue | readQueue");
    for (size_t i = 0; i < MAX_FD; i++) {
        if (pipeTable[i] != NULL) {
            // readfd
            if (pipeTable[i]->readOpen)
                printnum(pipeTable[i]->readfd);
            else
                print("-");
            print(" | ");

            // writefd
            if (pipeTable[i]->writeOpen)
                printnum(pipeTable[i]->writefd);
            else
                print("-");
            print(" | ");

            // bytesToRead
            printnum(pipeTable[i]->writeIdx - pipeTable[i]->readIdx);
            print(" | ");

            // readPid
            if (pipeTable[i]->readpid)
                printnum(pipeTable[i]->readpid);
            else
                print("-");
            print(" | ");

            // writePid
            if (pipeTable[i]->writepid)
                printnum(pipeTable[i]->writepid);
            else
                print("-");
            print(" | ");

            // print writequeue pids
            // print readqueue pids

            newLine();
        }
    }
}