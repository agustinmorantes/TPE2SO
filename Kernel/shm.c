#include <stdint.h>
#include <memory_manager.h>

#define MAX_SHM_COUNT 50
#define DEFAULT_SIZE 4096

typedef uint64_t shmID;

static void * created[MAX_SHM_COUNT];

void * shmOpen(shmID id) {
    if (id >= MAX_SHM_COUNT)
        return NULL;
    if (created[id])
        return created[id];
    void * mem = alloc(DEFAULT_SIZE);
    created[id] = mem;
    return mem; 
}