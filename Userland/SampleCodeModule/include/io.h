#ifndef IO__H
#define IO__H

#define EOF -1
#define STDOUT 0 
#define STDIN 1
#define STDERR 2

int printf(const char * format, ...);
int scanf(const char * format, ...);
int putchar(char c);
int getchar();
void clearTerminal();

#endif