#pragma once
#include <stdint.h>

#define CMD_COUNT 13

typedef int (*CmdHandler)(int argc, const char* argv[]);

typedef struct {
	const char* name;
	CmdHandler handler;
	uint8_t isBackground;
} Command;

int cmd_lscmd();
int cmd_clear();
int cmd_greet();
int cmd_time();
int cmd_printmem();
int cmd_inforeg();
int cmd_printcpufeatures();
int cmd_divbyzero();
int cmd_invalidopcode();
int cmd_roots();
int cmd_suma();
int cmd_background_test();

static Command commands[] = {
	{"help",cmd_lscmd,0},
	{"lscmd",cmd_lscmd,0},
	{"clear",cmd_clear,0},
	{"greet",cmd_greet,0},
	{"time",cmd_time,0},
    {"printmem", cmd_printmem,0},
    {"inforeg", cmd_inforeg,0},
	{"printcpufeatures", cmd_printcpufeatures,0},
	{"divbyzero", cmd_divbyzero,0},
	{"invalidopcode", cmd_invalidopcode,0},
	{"roots", cmd_roots,0},
	{"suma", cmd_suma,0},
	{"bgtest",cmd_background_test,0}
};
