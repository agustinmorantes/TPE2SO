#pragma once
#include <processManagement.h>
#include <stdint.h>

void * scheduler(void * rsp);
int schedulerAddProcess(PCB pcb);
PID getpid(void);
Background getBackground();
int setBackground(PID pid, Background background);
int64_t blockProcess(PID pid);
int64_t unblockProcess(PID pid);
int64_t terminateProcess(PID pid);
int64_t changePriority(PID pid, Priority priority);
void yield(void);
void _int20(void);
