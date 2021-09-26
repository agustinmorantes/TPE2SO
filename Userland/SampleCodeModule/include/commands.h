#pragma once

#define CMD_COUNT 12

typedef int (*CmdHandler)(int argc, const char* argv[]);

typedef struct {
	const char* name;
	CmdHandler handler;
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

static Command commands[] = {
	{"help",cmd_lscmd},
	{"lscmd",cmd_lscmd},
	{"clear",cmd_clear},
	{"greet",cmd_greet},
	{"time",cmd_time},
    {"printmem", cmd_printmem},
    {"inforeg", cmd_inforeg},
	{"printcpufeatures", cmd_printcpufeatures},
	{"divbyzero", cmd_divbyzero},
	{"invalidopcode", cmd_invalidopcode},
	{"roots", cmd_roots},
	{"suma", cmd_suma}
};
