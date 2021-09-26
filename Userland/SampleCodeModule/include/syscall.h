#pragma once

#include <stdint.h>
#include <currentTime.h>

int64_t _syswrite(uint64_t fd, const char* buf, uint64_t count);
int64_t _sysread(uint64_t fd, char* buf, uint64_t count);
int64_t _systime(Time* res);
void _sysclear();
void _sysprintmem(const void* ptr);
void _sysswitchterminal();
void _systerminalraw(uint8_t rawMode);
uint64_t _sysgetcurrentterminal();
