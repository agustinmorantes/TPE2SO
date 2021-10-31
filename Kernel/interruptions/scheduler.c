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

void forkfd(int fd[]) {
    for (int i = 0; i < MAX_FD; i++)
        fd[i] = readyList.current->pcb.fd[i];
}

int schedulerAddProcess(PCB pcb) {
    if(pcb.pid == 0) {
        haltRsp = pcb.rsp;
        return 0;
    }

    ProcessNode * newReady = alloc(sizeof(ProcessNode));
    if (newReady == NULL) return -1;
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
    return 0;
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

ProcessNode * searchNode(PID pid) {
    ProcessNode * node = searchReadyNode(pid);
    if(node == NULL) node = searchBlockedNode(pid);
    if(node == NULL) return NULL;
    return node;
}

int setBackground(PID pid, Background background) {
    ProcessNode * node = searchNode(pid);
    if(node == NULL) return -1;

    node->pcb.background = background;
    return 0;
}

Background getBackground() {
    return readyList.current->pcb.background;
}

int mapStdFds(PID pid, int stdin, int stdout) {
    ProcessNode* node = searchNode(pid);
    if(node == NULL) return -1;
    if (node->pcb.fd[stdin] == -1 || node->pcb.fd[stdout] == -1) 
        return -1;

    node->pcb.fd[0] = stdin;
    node->pcb.fd[1] = stdout;
    return 0;
}

int fdLocalToGlobal(int fd) {
    return readyList.current->pcb.fd[fd];
}

void addFd(uint32_t fd) {
    if (fd >= MAX_FD) return;
    readyList.current->pcb.fd[fd] = fd;
}

void removeFd(uint32_t fd) {
    if (fd >= MAX_FD) return;
    readyList.current->pcb.fd[fd] = -1;
}

int64_t changePriority(PID pid, Priority priority) {
    ProcessNode * process = searchReadyNode(pid);
    if (!process) process = searchBlockedNode(pid);
    if (process) {
        process->pcb.priority = priority;
        if (process->priorityCounter > priority)
            process->priorityCounter = priority;
        return priority;
    }
    return -1;
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

int64_t blockProcess(PID pid) {
    if (readyList.current->pcb.pid == pid) {
        readyList.current->pcb.state = BLOCKED;
        _int20();
        return 0;
    }
    ProcessNode * process = searchReadyNode(pid);
    if (process) {
        process->pcb.state = BLOCKED;
        removeBlocked(process);
        return 0;
    }
    return -1;
}

int64_t unblockProcess(PID pid) {
    ProcessNode * process = searchBlockedNode(pid);
    if (process) {
        process->pcb.state = READY;

        if (process->pcb.pid == blockedList.first->pcb.pid) {
            blockedList.first = blockedList.first->next;
            blockedList.first->prev = NULL;
        } else {
            process->prev->next = process->next;
            process->next->prev = process->prev;
        } 

        if (readyList.count == 0) {
            process->next = process;
            process->prev = process;
            readyList.current = process;
        } else {
            process->prev = readyList.current;
            process->next = readyList.current->next;
            readyList.current->next->prev = process;
            readyList.current->next = process;
        }
        readyList.count++;

        return 0;
    }
    return -1;
}

void removeTerminated(ProcessNode * terminated) {
    if (terminated->pcb.pid == readyList.current->pcb.pid) {
        if (readyList.count > 1) {
            readyList.current->prev->next = readyList.current->next;
            readyList.current->next->prev = readyList.current->prev;
            readyList.current = readyList.current->next;
        } else 
            readyList.current = NULL;
        readyList.count--;
    } else {
        if (terminated->pcb.pid == blockedList.first->pcb.pid) {
            blockedList.first = blockedList.first->next;
            if (blockedList.first != NULL)
                blockedList.first->prev = NULL;
        } else {
            terminated->prev->next = terminated->next;
            if (terminated->next != NULL)
                terminated->next->prev = terminated->prev;
        } 
    }

    for (size_t i = 3; i < MAX_FD; i++)
        closefd(terminated->pcb.fd[i]);
    
    free(terminated->pcb.memStart);
    free(terminated);
}

int64_t terminateProcess(PID pid) {
    if (readyList.current->pcb.pid == pid) {
        readyList.current->pcb.state = TERMINATED;
        _int20();
        return 0;
    }
    ProcessNode * process = searchReadyNode(pid);
    if (process) {
        process->pcb.state = TERMINATED;
        return 0;
    }
    process = searchBlockedNode(pid);
    if (process) {
        process->pcb.state = TERMINATED;
        removeTerminated(process);
        return 0;
    }
    
    return -1;
}

static int firstTime = 1;

void * scheduler(void * rsp) {
    if (haltRsp == 0) // not initialized
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
        removeTerminated(readyList.current);
    else if (readyList.current->pcb.state == BLOCKED)
        removeBlocked(readyList.current);
    else if (readyList.current->priorityCounter == 0) {
        readyList.current->priorityCounter = readyList.current->pcb.priority;
        readyList.current = readyList.current->next;
    }
    readyList.current->priorityCounter--;

    while (readyList.current->pcb.state == TERMINATED)
        removeTerminated(readyList.current);

    if (readyList.count == 0) {
        halt = 1;
        return haltRsp;
    }
    
    return readyList.current->pcb.rsp;
}

void yield() {
    readyList.current->priorityCounter = 0;
    _int20();
}

void listProcesses() {
    println("Lista de procesos del sistema");
    println("pid | name | state | rsp | stackStart | priority | fg/bg");
    ProcessNode * iterator = readyList.current;
    for (int i = 0; i < readyList.count ; i++, iterator = iterator->next) {
        printProcess(iterator);
    }
    iterator = blockedList.first;
    while (iterator != NULL) {
        printProcess(iterator);
        iterator = iterator->next;
    }
}

void printProcess(ProcessNode * process) {
    // pid
    printnum(process->pcb.pid);
    print(" | ");

    // name
    print(process->pcb.argv[0]);
    print(" | ");

    // state
    switch (process->pcb.state) {
        case READY:
            print("ready");
            break;
        case TERMINATED:
            print("terminated");
            break;
        case BLOCKED:
            print("blocked");
            break;
    }
    print(" | ");

    // rsp
    print("0x");
    printhex(process->pcb.rsp);
    print(" | ");

    // stack start
    print("0x");
    printhex(process->pcb.memStart + PROC_MEM);
    print(" | ");

    // priority
    switch (process->pcb.priority) {
        case LOW:
            print("low");
            break;
        case MEDIUM:
            print("medium");
            break;
        case HIGH:
            print("high");
            break;
    }
    print(" | ");

    // fg/bg
    switch (process->pcb.background) {
        case BACKGROUND:
            print("background");
            break;
        case FOREGROUND:
            print("foreground");
            break;
    }
    newLine();
}