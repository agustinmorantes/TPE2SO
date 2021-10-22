#pragma once
#include <processManagement.h>
#include <stdint.h>

void initScheduler(void);

uint64_t scheduler(uint64_t rsp);
void schedulerAddProcess(PCB pcb);
PID getpid(void);
void blockProcess(void);
void unblockProcess(PID pid);
void terminateProcess(void);
void _int20();
