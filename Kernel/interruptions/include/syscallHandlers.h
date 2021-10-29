#pragma once

#include <stdint.h>
#include <rtc.h>
#include <pipe.h>
#include <processManagement.h>

int64_t write(uint64_t fd, const char* buf, uint64_t count);
int64_t read(uint64_t fd, char* buf, uint64_t count);
int64_t time(Time* res);
void clearTerminalSyscall();
void setTerminalRawMode(uint8_t setRaw);
void printmem(const void* ptr);
void exit(void);
PID getPidSyscall(void);
int64_t kill(PID pid);
int64_t changePrioritySyscall(PID pid, Priority priority);
int64_t blockProcessSyscall(PID pid);
int64_t unblockProcessSyscall(PID pid);
void yieldSyscall(void);
int64_t pipeSyscall(uint64_t fd[2]);
int64_t close(uint64_t fd);
int64_t mkfifoSyscall(uint64_t id);
int64_t openFifoSyscall(uint64_t id, fdType type);
int setBackgroundSyscall(PID pid, Background background);
int mapStdFdsSyscall(PID pid, int stdin, int stdout);
int64_t rmFifoSyscall(uint64_t id);
void listPipesSyscall();
void listProcessSyscall();