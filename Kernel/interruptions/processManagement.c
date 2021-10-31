#include <processManagement.h>
#include <memory_manager.h>
#include <console.h>
#include <interrupts.h>
#include <scheduler.h>

#define DEFAULT_PRIORITY MEDIUM
#define DEFAULT_BACKGROUND BACKGROUND

static PID pid = 0;

#pragma pack(push, 1)
typedef struct {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
} RegState;

typedef struct {
    RegState regs;
    void* rip;
    void* cs;
    uint64_t rflags;
    void* rsp;
    void* ss;
    uint64_t align;
} ProcState;
#pragma pack(pop)

PID processCreate(void* program, unsigned int argc, char** argv) {
    void* memStart = alloc(PROC_MEM);
    if (memStart == NULL) 
        return -1;
    
    void* memEnd = (char*)memStart + PROC_MEM - 1;

    for(uint8_t* i = (uint8_t*)memStart; i <= memEnd; i++)
        *i = 0;

    ProcState* p = (ProcState*)((char*)memEnd - sizeof(ProcState) + 1);

    p->cs = 8;
    p->rsp = p->regs.rbp = memEnd;
    p->rflags = 0x202;
    p->rip = program;

    p->regs.rdi = (uint64_t)argc;
    p->regs.rsi = (uint64_t)argv;

    PCB pcb;

    pcb.pid = pid;
    pcb.rsp = &(p->regs);
    pcb.state = READY;
    pcb.memStart = memStart;
    pcb.argc = argc;
    pcb.argv = argv;
    pcb.priority = DEFAULT_PRIORITY;
    pcb.background = DEFAULT_BACKGROUND;
    if (pid == 1) { // si es el primer proceso le abro los std fds
        pcb.fd[0] = 0;
        pcb.fd[1] = 1;
        pcb.fd[2] = 2;
        for (int i = 3; i < MAX_FD; i++)
            pcb.fd[i] = -1;
    } else if (pid > 1) // si es otro le doy los del padre
        forkfd(pcb.fd);
    pid++;
    
    if(schedulerAddProcess(pcb) < 0) {
        free(memStart);
        return -1;
    }

    return pcb.pid;
}
