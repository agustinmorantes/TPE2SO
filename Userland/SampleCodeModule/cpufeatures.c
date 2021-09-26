#include <stdint.h>
#include <cpufeatures.h>
#include <io.h>

uint64_t _getCpuFeatures();
uint64_t _getExtendedCpuFeatures();

uint8_t getcpufeature(CpuFeature feature) {
    uint64_t features;
    if (feature < 64)
        features = _getCpuFeatures();
    else
        features = _getExtendedCpuFeatures();

    features = features >> (uint64_t) feature;
    features = features & 1;
    return features;
}

void printcpufeatures() {
    printf("CPU Features: \n");
    uint64_t cpuidSupport = _testCpuidSupport();
    printf("CPUID: %s\n", cpuidSupport? "Enabled": "Disabled");
    if (!cpuidSupport) return;
    printf("MMX: %s\n", getcpufeature(mmx_support)? "Enabled": "Disabled");
    printf("SSE: %s\n", getcpufeature(sse_support)? "Enabled": "Disabled");
    printf("SSE2: %s\n", getcpufeature(sse2_support)? "Enabled": "Disabled");
    printf("SSE3: %s\n", getcpufeature(sse3_support)? "Enabled": "Disabled");
    printf("SSE4.1: %s\n", getcpufeature(sse41_support)? "Enabled": "Disabled");
    printf("SSE4.2: %s\n", getcpufeature(sse42_support)? "Enabled": "Disabled");
    printf("AESNI: %s\n", getcpufeature(aesni_support)? "Enabled": "Disabled");
    printf("PCLMULQDQ: %s\n", getcpufeature(pclmulqdq_support)? "Enabled": "Disabled");
    printf("AVX: %s\n", getcpufeature(avx_support)? "Enabled": "Disabled");
    printf("VAESNI: %s\n", getcpufeature(vaesni_support)? "Enabled": "Disabled");
    printf("VPCLMULQDQ: %s\n", getcpufeature(vpclmulqdq_support)? "Enabled": "Disabled");
    printf("F16C: %s\n", getcpufeature(f16c_support)? "Enabled": "Disabled");
    printf("FMA: %s\n", getcpufeature(fma_support)? "Enabled": "Disabled");
    printf("AVX2: %s\n", getcpufeature(avx_support)? "Enabled": "Disabled");
}