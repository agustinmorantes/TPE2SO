#pragma once

#include <stdint.h>
#include <currentTime.h>

typedef int PID;

typedef enum Priority {
    LOW = 1,
    MEDIUM,
    HIGH,
} Priority;

typedef enum Background {
    FOREGROUND = 0,
    BACKGROUND = 1
} Background;

int64_t _syswrite(uint64_t fd, const char* buf, uint64_t count);
int64_t _sysread(uint64_t fd, char* buf, uint64_t count);
int64_t _systime(Time* res);
void _sysclear();
void _sysprintmem(const void* ptr);
void _systerminalraw(uint8_t rawMode);

void _sysexit();
PID _sysgetpid();
int64_t _syskill(PID pid);
int64_t _syschgpriority(PID pid, Priority priority);
int64_t _sysblock(PID pid);
int64_t _sysunblock(PID pid);
void _sysyield();
PID _syscreateprocess(void* program, unsigned int argc, char** argv);
int _syssetbackground(PID pid, Background background);
