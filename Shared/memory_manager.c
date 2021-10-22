#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_SIZE 1048576 // 1Mb
#define START_MM 0x900000
#define BYTE_ALIGMENT 8
#define ALIGMENT_MASK 0x0007
#define MINIMUM_BLOCK_SIZE (( size_t ) structSize << 1)
#define BITS_PER_BYTE (( size_t ) 8)

typedef struct freeNode 
{
    struct freeNode * next;
    size_t nodeSize;
} freeNode;

static freeNode start;
static freeNode * end = NULL;
static const size_t nodeSize = ( sizeof( freeNode ) + ( ( size_t ) ( BYTE_ALIGMENT - 1 ) ) ) & ~( ( size_t ) ALIGMENT_MASK );
static size_t freeBytesRemaining = 0U;
static size_t nodeAllocatedBit = 0;

static void addNodeToFreeList(freeNode toAdd);

static void listInit() 
{
    freeNode * first;
    uint8_t alignedHeap;
    size_t startAddress = (size_t) START_MM;
    size_t totalHeapSize = (size_t) MAX_SIZE;

    if ((startAddress & ALIGMENT_MASK) != 0 )
    {
        startAddress += (BYTE_ALIGMENT - 1);
        startAddress &= ~((size_t) ALIGMENT_MASK);
        totalHeapSize -= startAddress - (size_t)START_MM;
    }


    
}

