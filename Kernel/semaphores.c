#include <semaphores.h>

typedef struct processNode {
    PID pid;
    struct processNode * next;
} processNode;

typedef struct processQueue {
    processNode * first;
    processNode * last;
} processQueue;

typedef struct semaphore {
    semID id;
    uint64_t value;
    spinlock lock;
    processQueue activeQueue;
    processQueue blockedQueue;    
    struct semaphore * next;
} semaphore;


static semaphore * semList = NULL;

static semaphore * searchSemaphore(semID searchID) {
    semaphore * iterator = semList;
    while (iterator != NULL) {
        if (iterator->id == searchID)
            return iterator;
        iterator = iterator->next;
    }
    return NULL;    
}

static void removeSemaphore(semID id) {
    semaphore * prev = semList;
    if (prev->id == id) {
        semList = semList->next;
        free(prev);
        return;
    }
    semaphore * iterator = semList->next;
    while (iterator != NULL) {
        if (iterator->id == id) {
            prev->next = iterator->next;
            free(iterator);
            return;
        }
        prev = prev->next;
        iterator = iterator->next;
    }
}

static void addToProcessQueue(processQueue * queue, PID pid, int isActiveQueue) {
    if (isActiveQueue) { // En la lista de activos veo que no haya repetidos, en la de bloqueados no es necesario
        processNode * it = queue->first;
        while (it != NULL) {
            // No agrego dos veces al mismo
            if (it->pid == pid)
                return;
            it = it->next;
        }
    }
    
    processNode * toAdd = alloc(sizeof(processNode));
    if (toAdd == NULL)
        return; 
    toAdd->pid = pid;
    toAdd->next = NULL;
    if (queue->first == NULL)
        queue->first = toAdd;
    else
        queue->last->next = toAdd;

    queue->last = toAdd;
}

static void removeFromQueue(processQueue * queue, PID pid) {
    processNode * it = queue->first;
    if (it == NULL) 
        return;
    if (it->pid == pid) {
        queue->first = it->next;
        if (it->next == NULL)
            queue->last = NULL;
        free(it);
        return;
    }

    while (it->next != NULL) {
        if (it->next->pid == pid) {
            processNode * aux = it->next;
            it->next = it->next->next;
            if (queue->last == aux)
                queue->last = it;
            free(aux);
            return;
        }
        it = it->next;
    }
}

static PID popBlockedQueue(processQueue * queue) {
    if (queue->first == NULL)
        return -1;
    processNode * toRemove = queue->first;
    PID pid = toRemove->pid;
    queue->first = queue->first->next;
    if (queue->first == NULL)
        queue->last = NULL;
    free(toRemove);
    return pid;
}

static void addSemaphore(semaphore * toAdd) {
    semaphore * it = semList;
    if (it == NULL) {
        semList = toAdd;
        return;
    }
    while (it->next != NULL)
        it = it->next;
    it->next = toAdd;
}

int semOpen(semID id, uint64_t value) {
    semaphore * toAdd = searchSemaphore(id);
    if (toAdd != NULL) {
        addToProcessQueue(&(toAdd->activeQueue), getpid(), 1);
        return 0;
    }
    toAdd = alloc(sizeof(semaphore));
    if (toAdd == NULL)
        return -1; // TODO NULL-Check
    toAdd->id = id;
    toAdd->value = value;
    toAdd->blockedQueue.first = NULL;
    toAdd->blockedQueue.last = NULL;
    toAdd->activeQueue.first = NULL;
    toAdd->activeQueue.last = NULL;
    addToProcessQueue(&(toAdd->activeQueue), getpid(), 1);
    initLock(&toAdd->lock);
    addSemaphore(toAdd);
    return 1;
}

static void wakeup(processQueue * queue) {
    PID pid = popBlockedQueue(queue);
    if (pid < 0) return;
    unblockProcess(pid);
}

static void sleep(processQueue * queue) {
    PID pid = getpid();
    addToProcessQueue(queue, pid, 0);
    blockProcess(pid);
}

static int verifyPID(processQueue * activeQueue, PID pid) {
    processNode * iterator = activeQueue->first;
    while (iterator != NULL) {
        if (iterator->pid == pid) {
            return 1;
        }
        iterator = iterator->next;
    }
    return 0;
}

static void printStats(semaphore * sem) {
    printnum(sem->id);
    print(" | ");
    printnum(sem->value);
    print(" | ");
    processNode * it = sem->blockedQueue.first;
    while (it != NULL) {
        printnum(it->pid);
        print(" ");
        it = it->next;
    }
    newLine();
}

void semPrintPIDs(semID id) {
    semaphore * iterator = semList;
    while (iterator != NULL) {
        if (iterator->id == id) {
            processNode * it = iterator->blockedQueue.first;
            while (it != NULL) {
                printnum(it->pid);
                print(" ");
                it = it->next;
            }
            return;
        }
        iterator = iterator->next;
    }
}

void semPrintAll() {
    println("SEMAPHORE ID | VALUE | BLOCKED PROCESSES");
    semaphore * it = semList;
    while (it != NULL) {
        printStats(it);
        it = it->next;
    }
}

int semWait(semID id) {
    semaphore * sem = searchSemaphore(id);
    if (sem == NULL)
        return -1;
    
    acquire(&(sem->lock));
    if (sem->value > 0)
        sem->value -= 1;
    else {
        release(&(sem->lock));
        sleep(&(sem->blockedQueue));
        acquire(&(sem->lock));
        sem->value -= 1;
    }
    release(&(sem->lock));
    return 0;
}

int semPost(semID id) {
    semaphore * sem = searchSemaphore(id);
    if (sem == NULL)
        return -1;
    
    acquire(&(sem->lock));
    sem->value += 1;
    wakeup(&(sem->blockedQueue));
    release(&(sem->lock));
    yield();
    return 0;
}

int semClose(semID id) {
    semaphore * sem = searchSemaphore(id);
    if (sem == NULL)
        return -1;

    if (!verifyPID(&(sem->activeQueue), getpid()))
        return -2;
    
    removeFromQueue(&(sem->activeQueue), getpid());
    if (sem->activeQueue.first == NULL)
        removeSemaphore(sem->id);
    return 1;
}

// only for kernel
int deleteSemaphore(semID id) {
    semaphore * sem = searchSemaphore(id);
    if (sem == NULL)
        return -1;
    removeSemaphore(sem->id);
    return 1;
}