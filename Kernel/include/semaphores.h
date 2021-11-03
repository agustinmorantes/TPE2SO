#pragma once

#include <stdint.h>
#include <spinlock.h>
#include <processManagement.h>
#include <scheduler.h>
#include <memory_manager.h>
#include <console.h>

typedef int semID;

int semOpen(semID id, uint64_t value);
int semWait(semID id);
int semPost(semID id);
int semClose(semID id);
void semPrintAll();
void semPrintPIDs(semID id);
int deleteSemaphore(semID id);