#include <stdlib.h>
#include <stdint.h>
#include <fd.h>
#include <pipe.h>
#include <memory_manager.h>
#include <scheduler.h>

#define PIPE_BUF 10

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

uint64_t openPipe(uint64_t fd[2]) {
    PIPE pipe = alloc(sizeof(struct Pipe));
    if (pipe == NULL)
        return -1;

    uint64_t id;

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