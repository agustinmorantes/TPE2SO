#pragma once

#include <stdint.h>
#include <spinlock.h>
#include <processManagement.h>

semaphore * open();

void wait(semaphore * sem);

void post(semaphore * sem);