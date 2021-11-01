#pragma once
#include <stdint.h>

#define CMD_COUNT 25

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
int cmd_fdMap_test();
int cmd_not_implemented();
int cmd_kill();
int cmd_nice();
int cmd_block();
int cmd_cat();
int cmd_wc();
int cmd_filter();

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
	{"bgtest",cmd_background_test,0},
	{"fdmaptest",cmd_fdMap_test,0},
	{"mem", cmd_not_implemented,0},
	{"ps", cmd_not_implemented, 0},
	{"kill", cmd_kill,0},
	{"nice", cmd_nice,0},
	{"block", cmd_block},
	{"sem", cmd_not_implemented,0},
	{"cat", cmd_cat,0},
	{"wc", cmd_wc,0},
	{"filter", cmd_filter,0},
	{"pipe", cmd_not_implemented,0},
	{"phylo", cmd_not_implemented,0}
};
