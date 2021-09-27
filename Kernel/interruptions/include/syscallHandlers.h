#pragma once

#include <stdint.h>
#include <rtc.h>

int64_t write(uint64_t fd, const char* buf, uint64_t count);
int64_t read(uint64_t fd, char* buf, uint64_t count);
int64_t time(Time* res);
void clearTerminalSyscall();
void setTerminalRawMode(uint8_t setRaw);
void printmem(const void* ptr);
