#pragma once

#include <color.h>

void initVideo();

void printc(const char* string, Color background, Color foreground);
void printcln(const char* string, Color background, Color foreground);
void print(const char* string);
void println(const char* string);

void printnumc(uint64_t num, Color background, Color foreground);
void printnum(uint64_t num);
void printhexc(uint64_t hex, Color background, Color foreground);
void printhex(uint64_t hex);
void printbinc(uint64_t bin, Color background, Color foreground);
void printbin(uint64_t bin);

void printchar(char c);
void printcharc(char, Color background, Color foreground);

void setScreenPos(unsigned int x, unsigned int y, uint8_t c, Color background, Color foreground);

void clearTerminalColor(Color background);
void clearTerminal();

uint64_t getCurrentTerminal();

void switchTerminal();
void newLine();
void resetCursor();
int getCursorPos();
uint8_t getColumns();
