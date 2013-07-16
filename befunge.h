#pragma once
#include "stack.h"
#include <stdint.h>

typedef struct Index
{
	uint8_t x, y;
} Index;

typedef struct InterpreterState
{
	Index ip;
	struct { int8_t dx, dy;} delta;
	Stack *data;
	uint8_t *instructions;
	uint32_t *colors;
	bool errorFlag;
} InterpreterState;

Index defaultIndex();
InterpreterState emptyInterpreter();
void runInterpreterStep(InterpreterState* state);
