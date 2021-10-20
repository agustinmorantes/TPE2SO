#include <stdio.h>
#include <stdint.h>

#define MAX_SIZE 64*1024*1024
#define START_MM 0x900000

static char * current;

void * alloc(size_t size) 
{
    if (current == 0)
        current = START_MM;
    
    size = size%16 ? size + (16 - size%16) : size;

    if (current + size > START_MM + MAX_SIZE)
        return NULL;

    void * aux = current;
    current += size;
    return aux;
}

void free(void * ptr)
{
    return;
}