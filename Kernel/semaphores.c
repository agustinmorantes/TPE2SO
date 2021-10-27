#include <semaphores.h>

typedef struct processNode {
    PID pid;
    struct processNode * next;
    struct processNode * prev;
} processNode;

// typedef struct processQueue {
//     processNode * first;
//     processNode * last;
// } processQueue;

typedef struct semaphore {
    semID id;
    uint64_t value;
    spinlock lock;
    processNode * processQueue;
    processNode * blockedQueue;    
    struct semaphore * next;
} semaphore;


static semaphore * semList = NULL;

static semaphore * searchSemaphore(semID searchID) {
    semaphore * iterator = semList;
    while (iterator != NULL)
    {
        if (iterator->id == searchID)
            return iterator;
        iterator = iterator->next;
    }
    return NULL;    
}

static void addToProcessQueue(processNode * processQueue, PID pid) {
    processNode * prev = processQueue;
    if (prev == NULL)
    {
        prev = alloc(sizeof(processNode));
        prev->pid = pid;
        prev->next = NULL;
        prev->prev = NULL;
        return;
    }
    processNode * it = processQueue->next;
    while (it != NULL)
    {
        if (it->pid == pid)
            return;
        prev = it;
        it = it->next;
    }
    it = alloc(sizeof(processNode));
    it->next = NULL;
    it->prev = prev;
    it->pid = pid;
    prev->next = it;
}

static void addSemaphore(semaphore * toAdd) {
    semaphore * it = semList;
    if (it == NULL) {
        semList = toAdd;
        return;
    }
    while (it->next != NULL)
        it->next = it->next->next;
    it->next = toAdd;
}

void semOpen(semID id, uint64_t value) {
    semaphore * toAdd = searchSemaphore(id);
    if (toAdd != NULL) {
        addToProcessQueue(toAdd->processQueue, getpid());
        return;
    }
    toAdd = alloc(sizeof(semaphore));
    if (toAdd == NULL)
        return; // TODO NULL-Check
    
    toAdd->value = value;
    toAdd->blockedQueue = NULL;
    toAdd->processQueue = NULL;
    initLock(&toAdd->lock);
    addSemaphore(toAdd);
}

void semWait(semID id);

void semPost(semID id) {
    semaphore * sem = searchSemaphore(id);
    if (sem == NULL)
        return; // TODO NULL-Check
    
    if (sem->blockedQueue == NULL)
    {
        acquire(&sem->lock);
        sem->value += 1;
        release(&sem->lock);
        return;
    }
    // Despertar a alguien
}