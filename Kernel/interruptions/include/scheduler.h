#pragma once
#include <processManagement.h>
#include <stdint.h>

void initScheduler(void);

void * scheduler(void * rsp);
void schedulerAddProcess(PCB pcb);
PID getpid(void);
int64_t blockProcess(PID pid);
int64_t unblockProcess(PID pid);
int64_t terminateProcess(PID pid);
int64_t changePriority(PID pid, Priority priority);
void yield(void);
void _int20(void);
