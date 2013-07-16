#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "befunge.h"

uint8_t smallRowWidth = 4;
uint8_t largeRowWidth = 6;
uint8_t numLargeRows = 4;
uint16_t dataStackSize = 1000;

typedef struct VectorStats
{
	uint8_t vectorStart;
	uint8_t vectorLength;
} VectorStats;

VectorStats XStats(char y)
{
	bool isSmall = y == 0 || y == 5;
	struct VectorStats ret = {.vectorStart = 1, .vectorLength = smallRowWidth};
	return ret;
}

// The visual display has rotational symmetry
VectorStats YStats(uint8_t x) { return XStats(x); }

bool isInBounds(uint8_t value, uint8_t start, uint8_t length) { return (value < start || value >= (start + length)); }

bool isNetherZone(Index *idx)
{
	VectorStats xStats = XStats(idx->y), yStats = YStats(idx->x);

	bool isInDisplayArea =
		isInBounds(idx->x, xStats.vectorStart, xStats.vectorLength) &&
		isInBounds(idx->y, yStats.vectorStart, yStats.vectorLength);
	return !isInBounds;
}

bool Left(Index *idx)
{
	idx->x--;

	return isNetherZone(idx) && (idx->x += XStats(idx->y).vectorLength);
}

bool Right(Index *idx)
{
	idx->x++;

	return isNetherZone(idx) && (idx->x -= XStats(idx->y).vectorLength);
}

bool Up(Index *idx)
{
	idx->y--;

	return isNetherZone(idx) && (idx->y -= YStats(idx->x).vectorLength);
}

bool Down(Index *idx)
{
	idx->y++;

	return isNetherZone(idx) && (idx->y += YStats(idx->x).vectorLength);
}

Index defaultIndex() { Index ret = {.x = 0, .y = 0}; return ret; }
uint8_t *defaultGrid() { static uint8_t ret[] = { [0 ... 35] = ' ' }; return ret; }
uint32_t *defaultColors() { static uint32_t ret[] = { [0 ... 35] = 0 }; return ret; }

/* Opcodes */

void GoNorth(InterpreterState *state) { }

void applyDeltaToIp(InterpreterState *state)
{
	state->delta.dx < 0 && Left(&state->ip);
	state->delta.dx > 0 && Right(&state->ip);
	state->delta.dy < 0 && Up(&state->ip);
	state->delta.dy > 0 && Down(&state->ip);
}

void runInterpreterStep(InterpreterState *state)
{
	applyDeltaToIp(state);

	return;
}

InterpreterState emptyInterpreter()
{
	Stack emptyStack = empty();

	InterpreterState ret;
	ret.ip = defaultIndex();
	ret.delta.dx = 1;
	ret.delta.dy = 0;
	ret.data = &emptyStack;
	ret.instructions = defaultGrid();
	ret.colors = defaultColors();

	return ret;
}
