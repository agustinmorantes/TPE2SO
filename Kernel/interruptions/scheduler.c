#include <stdint.h>
#include <scheduler.h>
#include <stdlib.h>
#include <memory_manager.h>
#include <interrupts.h>
#include <console.h>

typedef struct ProcessNode {
    struct ProcessNode * prev;
    struct ProcessNode * next;
    PCB pcb;
    size_t priorityCounter;
} ProcessNode;

typedef struct {
    ProcessNode * first;
} BlockedList;

typedef struct {
    ProcessNode * current;
    size_t count;
} ReadyList;

static ReadyList readyList;
static BlockedList blockedList;
static void * haltRsp;

static uint64_t halt = 0;

static int enabled = 0;

void initScheduler() {
    enabled = 1;
}

void schedulerAddProcess(PCB pcb) {
    if(pcb.pid == 0) {
        haltRsp = pcb.rsp;
        return;
    }

    ProcessNode * newReady = alloc(sizeof(ProcessNode));
    newReady->pcb = pcb;
    newReady->priorityCounter = pcb.priority;

    if (readyList.count == 0) {
        newReady->next = newReady;
        newReady->prev = newReady;
        readyList.current = newReady;
    } else {
        newReady->next = readyList.current;
        newReady->prev = readyList.current->prev;

        readyList.current->prev->next = newReady;
        readyList.current->prev = newReady;
    }
    readyList.count++;
}

PID getpid() {
    return readyList.current->pcb.pid;
}

ProcessNode * changeProcessState(PID pid, State state) {
    // si es el proceso actual lo saco con una int 20h
    if (readyList.current->pcb.pid == pid) {
        readyList.current->pcb.state = state;
        _int20();
        return NULL;
    }

    // si no primero busco en la cola de listos
    ProcessNode * iterator = readyList.current;
    for (int i = 0; i < readyList.count ; i++, iterator = iterator->next) {
        if (iterator->pcb.pid == pid) {
            iterator->pcb.state = state;
            return iterator;
        }
    }

    // si no lo encontre busco en la cola de bloqueados
    if (state != BLOCKED) {
        iterator = blockedList.first;
        while (iterator != NULL) {
            if (iterator->pcb.pid == pid) {
                iterator->pcb.state = state;
                return iterator;
            }
        iterator = iterator->next;
        }    
    }
    return NULL;
}

void removeBlocked(ProcessNode * blocked) {
    if (blocked->pcb.pid == readyList.current->pcb.pid) {
        if (readyList.count > 1) { 
            blocked->prev->next = blocked->next;
            blocked->next->prev = blocked->prev;
            readyList.current = readyList.current->next;
        } else 
            readyList.current = NULL;
    } else {
        blocked->prev->next = blocked->next;
        blocked->next->prev = blocked->prev;
    }
    
    readyList.count--;

    blocked->next = NULL;
    blocked->prev = NULL;
    blocked->priorityCounter = blocked->pcb.priority;

    if (blockedList.first == NULL) {
        blockedList.first = blocked;
    } else {
        blocked->next = blockedList.first;
        blockedList.first = blocked;
    }
}

void blockProcess(PID pid) {
    ProcessNode * blocked = changeProcessState(pid, BLOCKED);
    if (blocked) removeBlocked(blocked);
}

void unblockProcess(PID pid) {
    ProcessNode * current = blockedList.first;
    while (current != NULL) {
        if (current->pcb.pid == pid) {
            current->pcb.state = READY;

            if (current->pcb.pid == blockedList.first->pcb.pid)
                blockedList.first = blockedList.first->next;

            current->prev = readyList.current;
            current->next = readyList.current->next;
            readyList.current->next->prev = current;
            readyList.current->next = current;
            
            readyList.count++;

            return;
        }
        current = current->next;
    }
}

void terminateProcess(PID pid) {
    changeProcessState(pid, TERMINATED);
}

void removeTerminated() {
    ProcessNode * terminated = readyList.current;

    if (readyList.count > 1) {
        readyList.current->prev->next = readyList.current->next;
        readyList.current->next->prev = readyList.current->prev;
        readyList.current = readyList.current->next;
    } else 
        readyList.current = NULL;

    readyList.count--;

    free(terminated->pcb.memStart);
    free(terminated);
}

static int firstTime = 1;

void * scheduler(void * rsp) {
    if (haltRsp == 0 || !enabled) // not initialized
        return rsp;

    if (halt)
        haltRsp = rsp;
    else if (!firstTime)
        readyList.current->pcb.rsp = rsp;
    halt = 0;
    firstTime = 0;
    
    if (readyList.count == 0) {
        halt = 1;
        return haltRsp;
    }

    if (readyList.current->pcb.state == TERMINATED) 
        removeTerminated();
    else if (readyList.current->pcb.state == BLOCKED)
        removeBlocked(readyList.current);
    else 
        readyList.current = readyList.current->next;
        
    if (readyList.count == 0) {
        halt = 1;
        return haltRsp;
    }
    
    return readyList.current->pcb.rsp;
}