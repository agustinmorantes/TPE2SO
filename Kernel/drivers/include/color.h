#pragma once

#include <stdint.h>

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} Color;

static const Color Black = {0,0,0};
static const Color White = {255,255,255};
static const Color LightGray = {200,200,200};
static const Color Gray = {128,128,128};
static const Color Yellow = {255,200,0};
static const Color Red = {255,20,0};
static const Color Blue = {0,150,255};
