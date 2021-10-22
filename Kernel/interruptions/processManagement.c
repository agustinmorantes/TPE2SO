#include <processManagement.h>
#include <memory_manager.h>
#include <console.h>
#include <interrupts.h>
#include <scheduler.h>

#define PROC_MEM_MB 1
#define PROC_MEM (PROC_MEM_MB * 1024 * 1024)

static PID pid = 0;

#pragma pack(push, 1)
typedef struct {
    void* rip;
    void* cs;
    uint64_t rflags;
    void* rsp;
    void* ss;
    uint64_t align;
} ProcState;

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
#pragma pack(pop)

PID processCreate(void* program, unsigned int argc, char** argv) {    
    void* memStart = alloc(PROC_MEM);
    void* memEnd = (char*)memStart + PROC_MEM - 1;

    for(uint8_t* i = (uint8_t*)memStart; i <= memEnd; i++)
        *i = 0;

    ProcState* p = (ProcState*)((char*)memEnd - sizeof(ProcState) + 1);
    RegState* registers = (RegState*)p - 1;

    p->cs = 8;
    p->rsp = registers->rbp = memEnd;
    p->rflags = 0x202;
    p->rip = program;

    PCB pcb;

    pcb.pid = pid++;
    pcb.rsp = registers;
    pcb.state = READY;
    pcb.memStart = memStart;

    schedulerAddProcess(pcb);

    return pcb.pid;
}
