#pragma once

#include <stdio.h>
#include <stdint.h>

void * alloc(unsigned long size);

void free(void * memptr);

size_t getFreeBytesRemaining();
size_t getTotalBytes();
size_t getUsedMemory();