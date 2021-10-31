#pragma once
#include <stdint.h>
#include <fd.h>

typedef int PID;

#define PROC_MEM (8*1024)
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

typedef enum Background {
    FOREGROUND = 0,
    BACKGROUND = 1
} Background;

typedef struct {
    PID pid;
    State state;
    void* rsp;
    void* memStart;
    unsigned int argc;
    const char** argv;
    Priority priority;
    Background background;
    int fd[MAX_FD];
} PCB;

PID processCreate(void* program, unsigned int argc, char** argv);
void processRun(PID pid);
