#pragma once
#include <stdint.h>

typedef int PID;

typedef enum State {
    READY = 1,
    BLOCKED,
    TERMINATED,
} State;

typedef struct {
    PID pid;
    State state;
    void* rsp;
    void* memStart;
} PCB;

PID processCreate(void* program, unsigned int argc, char** argv);
void processRun(PID pid);
