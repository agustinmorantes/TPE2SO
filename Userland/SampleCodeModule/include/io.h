#pragma once

#define EOF -1
#define STDIN 0
#define STDOUT 1
#define STDERR 2 

int printf(const char * format, ...);
int scanf(const char * format, ...);
int putchar(char c);
int getchar();
void clearTerminal();
