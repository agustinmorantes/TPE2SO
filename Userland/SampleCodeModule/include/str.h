#ifndef STR_H
#define STR_H
#include <stdint.h>

uint8_t isWhitespace(char c);
uint64_t strlen(const char * s);
int8_t strcmp(const char* str1, const char* str2);
uint64_t strcpy(char * to, const char * from);
uint64_t strncpy(char * to, const char * from, int n);
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
uint64_t strToIntBase(const char * s, int len, uint32_t base, int * result, int unsign);
uint8_t isNumber(char c);
uint32_t floatToStr(double value, char * buffer, uint32_t decimals);
int64_t strToFloat(const char * s, int len, double * result);


#endif