#pragma once

#define EDX 0
#define ECX 32
#define EXT_EBX 64
#define EXT_ECX 96

typedef enum CpuFeature {
    mmx_support = EDX + 23,
    sse_support = EDX + 25,
    sse2_support = EDX + 26,
    sse3_support = ECX + 0,
    sse41_support = ECX + 19,
    sse42_support = ECX + 20,
    aesni_support = ECX + 25,
    pclmulqdq_support = ECX + 1,
    avx_support = ECX + 28,
    vaesni_support = EXT_ECX + 9,
    vpclmulqdq_support = EXT_ECX + 10,
    f16c_support = ECX + 29,
    fma_support = ECX + 12,
    avx2_support = EXT_EBX + 5
} CpuFeature;

uint64_t _testCpuidSupport();

uint8_t getcpufeature(CpuFeature feature);

void printcpufeatures();
