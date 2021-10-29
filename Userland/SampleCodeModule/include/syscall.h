#pragma once

#include <stdint.h>
#include <currentTime.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2 

typedef int PID;
typedef int semID;

typedef enum Priority {
    LOW = 1,
    MEDIUM,
    HIGH,
} Priority;

typedef enum Background {
    FOREGROUND = 0,
    BACKGROUND = 1
} Background;

typedef enum fdType {
    READ = 0,
    WRITE,
} fdType;


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
int64_t _syspipe(uint64_t fd[2]);
int64_t _sysclose(uint64_t fd);
int64_t _sysmkfifo(uint64_t id);
int64_t _sysopenfifo(uint64_t id, fdType type);
int _sysmapstdfds(PID pid, int stdin, int stdout);
int64_t _sysrmfifo(uint64_t id);
void _syslistpipes();
void _syslistprocesses();
int _semopen(semID id, uint64_t value);
int _semwait(semID id);
int _sempost(semID id);
int _semclose(semID id);
void _syslistsem();
