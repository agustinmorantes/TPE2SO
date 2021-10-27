#pragma once

#include <stdint.h>
#include <spinlock.h>
#include <processManagement.h>
#include <scheduler.h>
#include <memory_manager.h>

typedef int semID;

void semOpen(semID id, uint64_t value);

void semWait(semID id);

void semPost(semID id);