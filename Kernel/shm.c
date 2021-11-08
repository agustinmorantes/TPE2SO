#include <shm.h>

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