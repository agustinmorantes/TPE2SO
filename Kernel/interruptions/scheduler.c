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

ProcessNode * searchReadyNode(PID pid) {
    ProcessNode * iterator = readyList.current;
    for (int i = 0; i < readyList.count ; i++, iterator = iterator->next) {
        if (iterator->pcb.pid == pid)
            return iterator;
    }
    return NULL;
}

ProcessNode * searchBlockedNode(PID pid) {
    ProcessNode * iterator = blockedList.first;
    while (iterator != NULL) {
        if (iterator->pcb.pid == pid)
            return iterator;
        iterator = iterator->next;
    }
    return NULL;
}

void changePriority(PID pid, Priority priority) {
    ProcessNode * process = searchReadyNode(pid);
    if (!process) process = searchBlockedNode(pid);
    if (process) {
        process->pcb.priority = priority;
        if (process->priorityCounter > priority)
            process->priorityCounter = priority;
    }
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
        blockedList.first->prev = blocked;
        blockedList.first = blocked;
    }
}

void blockProcess(PID pid) {
    if (readyList.current->pcb.pid == pid) {
        readyList.current->pcb.state = BLOCKED;
        _int20();
        return;
    }
    ProcessNode * process = searchReadyNode(pid);
    if (process) {
        process->pcb.state = TERMINATED;
        removeBlocked(process);
    }
}

void unblockProcess(PID pid) {
    ProcessNode * iterator = blockedList.first;
    while (iterator != NULL) {
        if (iterator->pcb.pid == pid) {
            iterator->pcb.state = READY;

            if (iterator->pcb.pid == blockedList.first->pcb.pid) {
                blockedList.first = blockedList.first->next;
                blockedList.first->prev = NULL;
            } else {
                iterator->prev->next = iterator->next;
                iterator->next->prev = iterator->prev;
            } 

            iterator->prev = readyList.current;
            iterator->next = readyList.current->next;
            readyList.current->next->prev = iterator;
            readyList.current->next = iterator;
            
            readyList.count++;

            return;
        }
        iterator = iterator->next;
    }
}

void terminateProcess(PID pid) {
    if (readyList.current->pcb.pid == pid) {
        readyList.current->pcb.state = TERMINATED;
        _int20();
        return;
    }
    ProcessNode * process = searchReadyNode(pid);
    if (!process) process = searchBlockedNode(pid);
    if (process) {
        process->pcb.state = TERMINATED;
    }
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
    else if (readyList.current->priorityCounter == 0) {
        readyList.current->priorityCounter = readyList.current->pcb.priority;
        readyList.current = readyList.current->next;
    }
    readyList.current->priorityCounter--;

    if (readyList.count == 0) {
        halt = 1;
        return haltRsp;
    }
    
    return readyList.current->pcb.rsp;
}