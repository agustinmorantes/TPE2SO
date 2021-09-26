#include <stdio.h>
#include <stdint.h>

#define MAX_SIZE 64*1024*1024

char * current = 0x900000;

void * alloc(size_t size) 
{
    if (size > current + MAX_SIZE)
    {
        return NULL;
    }
    void * aux = current;
    current += size;
    return aux;
}

void free(void * ptr)
{
    return;
}