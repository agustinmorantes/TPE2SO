#include <pipe.h>
#include <fd.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_FD 255

typedef struct fd {
    uint64_t ref;
    fdType type;
    PIPE pipe;
} FD;

static FD fdTable[MAX_FD]; 

uint64_t initfd(fdType type, PIPE pipe) {
    for(size_t i = 3; i < MAX_FD; i++){
        if(fdTable[i].ref == 0) {
            fdTable[i].ref = 1;
            fdTable[i].type = type;
            fdTable[i].pipe = pipe;
            return i;
        }
    }
    return -1;
}

void closefd(uint64_t id) {
    fdTable[id].ref--;
    if (fdTable[id].ref == 0) {
        closePipe(fdTable[id].pipe, fdTable[id].type);
        fdTable[id].pipe = NULL;
    }
}

void fddup(uint64_t id) {
    if (fdTable[id].ref)
        fdTable[id].ref++;
}

int64_t readfd(uint64_t fd, char* buf, uint64_t count) {
    if (fdTable[fd].type != READ) 
        return -1;
    return readPipe(fdTable[fd].pipe, buf, count);    
}

int64_t writefd(uint64_t fd, const char* buf, uint64_t count) {
    if (fdTable[fd].type != WRITE) 
        return -1;
    return writePipe(fdTable[fd].pipe, buf, count);    
}

