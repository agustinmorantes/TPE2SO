#include <stdlib.h>
#include <stdint.h>
#include <fd.h>
#include <pipe.h>
#include <memory_manager.h>
#include <scheduler.h>

#define PIPE_BUF 4096
#define MAX_FIFO 64

struct Pipe {
    char buf[PIPE_BUF];
    uint32_t readIdx;
    uint32_t writeIdx;
    int readOpen;
    int writeOpen;
    int readpid;
    int writepid;
    // sem writequeue
    // sem readqueue
};

typedef struct fifo {
    uint64_t id;
    uint64_t readfd;
    uint64_t writefd;
} FIFO;

static FIFO fifoTable[MAX_FIFO];

int64_t mkfifo(uint64_t id) {
    if (id == 0) return -1; // 0 not a valid id
    int64_t k = -1;
    for (int64_t i = 0; i < MAX_FIFO; i++) {
        if (fifoTable[i].id == id) // ya existe
            return -1;
        if (fifoTable[i].id == 0) // encontre lugar
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
    
    return 0;
}

void closePipe(PIPE pipe, fdType type) {
    if (type == READ)
        pipe->readOpen = 0;
    else if (type == WRITE)
        pipe->writeOpen = 0;
    
    if (!pipe->readOpen && !pipe->writeOpen)    
        free(pipe);
}

int64_t readPipe(PIPE pipe, char* buf, uint64_t count) {
    if (!pipe->readOpen)
        return -1;

    if (!pipe->writeOpen)
        return 0;

    // semwait readqueue

    pipe->readpid = getpid();
    while (pipe->readIdx == pipe->writeIdx) {
        if (!pipe->writeOpen) {
            pipe->readpid = 0;
            // sempost readqueue
            return 0;
        }
        blockProcess(pipe->readpid);
    }
    pipe->readpid = 0;

    int i;
    for(i = 0; i < count; i++) {
        if(pipe->readIdx == pipe->writeIdx)
            break;
        buf[i] = pipe->buf[pipe->readIdx++ % PIPE_BUF];
    }

    if (pipe->writepid)
        unblockProcess(pipe->writepid);

    // sempost readqueue
    return i;
}

int64_t writePipe(PIPE pipe, const char* buf, uint64_t count) {
    if (!pipe->writeOpen || !pipe->readOpen)
        return -1;

    // semwait writequeue

    for(int i = 0; i < count; i++) {
        pipe->writepid = getpid();
        while(pipe->writeIdx == pipe->readIdx + PIPE_BUF) {
            if(!pipe->readOpen) {
                pipe->writepid = 0;
                // sempost writequeue
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

    // sempost writequeue

    return count;
}