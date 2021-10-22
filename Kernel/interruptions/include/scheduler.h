#pragma once
#include <processManagement.h>
#include <stdint.h>

void initScheduler(void);

void * scheduler(void * rsp);
void schedulerAddProcess(PCB pcb);
PID getpid(void);
void blockProcess(PID pid);
void unblockProcess(PID pid);
void terminateProcess(PID pid);
void _int20(void);
