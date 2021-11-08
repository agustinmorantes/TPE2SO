#pragma once

#include <stdint.h>
#include <memory_manager.h>

#define MAX_SHM_COUNT 50
#define DEFAULT_SIZE 4096

typedef uint64_t shmID;

void * shmOpen(shmID id);