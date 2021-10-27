#include <semaphores.h>

typedef struct processNode {
    PID pid;
    struct processNode * next;
} processNode;

typedef int semID;

typedef struct {
    uint64_t value;
    spinlock lock;
    processNode * processQueue;
    processNode * blockedQueue;    
} semaphore;

typedef struct semaphoresQueue {
    struct semephoreQueue * next;
    semaphore
};



semaphore * open() {

}

void wait(semaphore * sem);

void post(semaphore * sem);