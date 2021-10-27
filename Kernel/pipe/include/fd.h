#pragma once
#include <stdint.h>
#include <pipe.h>

uint64_t initfd(fdType type, PIPE pipe);
void closefd(uint64_t id);
void fddup(uint64_t id);

int64_t readfd(uint64_t fd, char* buf, uint64_t count);
int64_t writefd(uint64_t fd, const char* buf, uint64_t count);