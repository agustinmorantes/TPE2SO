#pragma once
#include <stdint.h>

typedef int PID;

typedef enum State {
    READY = 1,
    BLOCKED,
    TERMINATED,
} State;

typedef enum Priority {
    LOW = 1,
    MEDIUM,
    HIGH,
} Priority;

typedef struct {
    PID pid;
    State state;
    void* rsp;
    void* memStart;
    Priority priority;
} PCB;

PID processCreate(void* program, unsigned int argc, char** argv, Priority priority);
void processRun(PID pid);
