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

void Left(Index *idx)
{
	idx->x--;

	isNetherZone(idx) && (idx->x += XStats(idx->y).vectorLength);
}

void Right(Index *idx)
{
	idx->x++;

	isNetherZone(idx) && (idx->x -= XStats(idx->y).vectorLength);
}

void Up(Index *idx)
{
	idx->y--;

	isNetherZone(idx) && (idx->y -= YStats(idx->x).vectorLength);
}

void Down(Index *idx)
{
	idx->y++;

	isNetherZone(idx) && (idx->y += YStats(idx->x).vectorLength);
}

void runIntepreterStep(InterpreterState *state)
{
}

