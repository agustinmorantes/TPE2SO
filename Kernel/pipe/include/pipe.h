#pragma once
#include <stdint.h>

typedef enum fdType {
    READ = 0,
    WRITE,
} fdType;

typedef struct Pipe * PIPE;

int64_t openPipe(uint64_t fd[2]);
void closePipe(PIPE pipe, fdType type);
int64_t readPipe(PIPE pipe, char* buf, uint64_t count);
int64_t writePipe(PIPE pipe, const char* buf, uint64_t count);

int64_t openFifo(uint64_t id, fdType type);
int64_t mkfifo(uint64_t id);