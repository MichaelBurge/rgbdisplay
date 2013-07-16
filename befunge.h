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
	uint8_t *instructions;
	uint32_t *colors;
} InterpreterState;

typedef enum Opcode {
	NoOp
} Opcode;

Index defaultIndex();
InterpreterState emptyInterpreter();
void runInterpreterStep(InterpreterState* state);
