#ifndef __EXCEPTONS__H
#define __EXCEPTONS__H

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6

#include <stdint.h>

#pragma pack(push, 1)
typedef struct
{
    uint64_t rsp;
    uint64_t rflags;
    uint64_t rip;
    uint64_t rbp;
    uint64_t rax;
    uint64_t rbx;
	uint64_t rcx;
	uint64_t rdx;
	uint64_t rdi;
	uint64_t rsi;
	uint64_t r8;
	uint64_t r9;
	uint64_t r10;
	uint64_t r11;
	uint64_t r12;
	uint64_t r13;
	uint64_t r14;
	uint64_t r15;
} Registers;
#pragma pack(pop)

#endif