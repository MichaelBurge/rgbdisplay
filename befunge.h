#pragma once
#include "stack.h"
#include <stdint.h>

typedef struct Index
{
	uint8_t x;
	uint8_t y;
} Index;

typedef struct InterpreterState
{
	Index ip;
	Stack *data;
	uint8_t instructions[6][6];
	uint32_t colors[6][6];
} InterpreterState;

void runInterpreterStep(InterpreterState* state);
