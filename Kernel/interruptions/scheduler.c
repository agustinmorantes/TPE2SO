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
} ProcessNode;

typedef struct {
    ProcessNode * first;
} BlockedList;

static ProcessNode * readyList;
static BlockedList blockedList;
static uint64_t haltRsp;

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

    if (readyList == NULL) {
        newReady->next = newReady;
        newReady->prev = newReady;
        readyList = newReady;
    } else {
        newReady->next = readyList;
        newReady->prev = readyList->prev;

        readyList->prev->next = newReady;
        readyList->prev = newReady;
    }
}

PID getpid() {
    return readyList->pcb.pid;
}

void blockProcess() {
    readyList->pcb.state = BLOCKED;
    _int20();
}

void removeBlocked() {
    ProcessNode * blocked = readyList;
    
    if (readyList->pcb.pid != readyList->next->pcb.pid) { // Si hay mas de un proceso
        readyList->prev->next = readyList->next;
        readyList->next->prev = readyList->prev;
        readyList = readyList->next;
    } else 
        readyList = NULL;

    blocked->next = NULL;
    blocked->prev = NULL;

    if (blockedList.first == NULL) {
        blockedList.first = blocked;
    } else {
        blocked->next = blockedList.first;
        blockedList.first = blocked;
    }
}

void unblockProcess(PID pid) {
    ProcessNode * current = blockedList.first;
    while (current != NULL) {
        if (current->pcb.pid == pid) {
            current->pcb.state = READY;

            if (current->pcb.pid == blockedList.first->pcb.pid)
                blockedList.first = blockedList.first->next;

            current->prev = readyList;
            current->next = readyList->next;
            readyList->next->prev = current;
            readyList->next = current;

            return;
        }
    }
}

void terminateProcess() {
    readyList->pcb.state = TERMINATED;
    _int20();
}

void removeTerminated() {
    ProcessNode * terminated = readyList;

    if (readyList->pcb.pid != readyList->next->pcb.pid) { // Si hay mas de un proceso
        readyList->prev->next = readyList->next;
        readyList->next->prev = readyList->prev;
        readyList = readyList->next;
    } else 
        readyList = NULL;

    free(terminated);

    // delete stack
}

static int firstTime = 1;

uint64_t scheduler(uint64_t rsp) {
    if (haltRsp == 0 || !enabled) // not initialized
        return rsp;

    if (halt)
        haltRsp = rsp;
    else if (!firstTime)
        readyList->pcb.rsp = rsp;
    halt = 0;
    firstTime = 0;
    
    if (readyList == NULL) {
        halt = 1;
        return haltRsp;
    }

    if (readyList->pcb.state == TERMINATED) 
        removeTerminated();
    else if (readyList->pcb.state == BLOCKED)
        removeBlocked();
    else 
        readyList = readyList->next;
        
    if (readyList == NULL) {
        halt = 1;
        return haltRsp;
    }
    
    return readyList->pcb.rsp;
}