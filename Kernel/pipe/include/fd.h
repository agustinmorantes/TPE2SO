#pragma once
#include <stdint.h>
#include <pipe.h>

#define MAX_FD 255

int64_t initfd(fdType type, PIPE pipe);
int64_t closefd(uint64_t id);
void fddup(uint64_t id);

int64_t readfd(uint64_t fd, char* buf, uint64_t count);
int64_t writefd(uint64_t fd, const char* buf, uint64_t count);