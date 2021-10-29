#pragma once

#include <stdint.h>
#include <spinlock.h>
#include <processManagement.h>
#include <scheduler.h>
#include <memory_manager.h>

typedef int semID;

int semOpen(semID id, uint64_t value);

int semWait(semID id);

int semPost(semID id);