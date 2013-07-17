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
	return !isInDisplayArea;
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

uint16_t indexToOffset(Index index) {
	uint16_t offset = index.x;
	while (index.y --> 0)
		offset += XStats(index.y).vectorLength;
	return offset;
};

Index defaultIndex() { Index ret = {.x = 0, .y = 0}; return ret; }
uint8_t *defaultGrid() { static uint8_t ret[] = { [0 ... 35] = ' ' }; return ret; }
uint32_t *defaultColors() { static uint32_t ret[] = { [0 ... 35] = 0 }; return ret; }

/* Opcodes */
/* http://quadium.net/funge/spec98.html */
typedef void (*Mutator)(InterpreterState*);

void IrrecoverableError(InterpreterState *state) { state->errorFlag = 1; }
void UnimplementedInstruction(InterpreterState *state) { state->errorFlag = 1; }
void DoNothing(InterpreterState *state) { return; }
// Direction Changing
void GoNorth(InterpreterState *state) { state->delta.dx =  0; state->delta.dy = -1; }
void GoSouth(InterpreterState *state) { state->delta.dx =  0; state->delta.dy = +1; }
void GoEast(InterpreterState *state)  { state->delta.dx = +1; state->delta.dy =  0; }
void GoWest(InterpreterState *state)  { state->delta.dx = -1; state->delta.dy =  0; }
void GoHigh(InterpreterState *state) { IrrecoverableError(state); }
void GoLow(InterpreterState *state) { IrrecoverableError(state); }
void GoRandom(InterpreterState *state) { Mutator jmp[] = {&GoNorth, &GoSouth, &GoWest, &GoEast}; jmp[rand()%4](state); }
void Reverse(InterpreterState *state) { state->delta.dx *= -1; state->delta.dy *= -1; }
void TurnRight(InterpreterState *state) { uint8_t old_dx = state->delta.dx; state->delta.dx = -state->delta.dy; state->delta.dy = state->delta.dx; }
void TurnLeft(InterpreterState *state) { Reverse(state), TurnRight(state), Reverse(state); }
void AbsoluteDelta(InterpreterState *state) { UnimplementedInstruction(state); }
// Flow Control
void Trampoline(InterpreterState *state) { UnimplementedInstruction(state); }
void Stop(InterpreterState *state) { UnimplementedInstruction(state); }
void JumpOver(InterpreterState *state) { UnimplementedInstruction(state); }
void JumpForward(InterpreterState *state) { UnimplementedInstruction(state); }
void Quit(InterpreterState *state) { UnimplementedInstruction(state); }
void Iterate(InterpreterState *state) { UnimplementedInstruction(state); }
// Decision Making
void LogicalNot(InterpreterState *state) { UnimplementedInstruction(state); }
void GreaterThan(InterpreterState *state) { UnimplementedInstruction(state); }
void EastWestIf(InterpreterState *state) { UnimplementedInstruction(state); }
void NorthSouthIf(InterpreterState *state) { UnimplementedInstruction(state); }
void HighLowIf(InterpreterState *state) { IrrecoverableError(state); }
void Compare(InterpreterState *state) { UnimplementedInstruction(state); }
// Integers
void Push(InterpreterState *state) { UnimplementedInstruction(state); }
void Add(InterpreterState *state) { UnimplementedInstruction(state); }
void Multiply(InterpreterState *state) { UnimplementedInstruction(state); }
void Subtract(InterpreterState *state) { UnimplementedInstruction(state); }
void Divide(InterpreterState *state) { UnimplementedInstruction(state); }
void Remainder(InterpreterState *state) { UnimplementedInstruction(state); }
// Strings
void ToggleStringmode(InterpreterState *state) { UnimplementedInstruction(state); }
void FetchCharacter(InterpreterState *state) { UnimplementedInstruction(state); }
void StoreCharacter(InterpreterState *state) { UnimplementedInstruction(state); }
// Stack Manipulation
void Pop(InterpreterState *state) { UnimplementedInstruction(state); }
void Duplicate(InterpreterState *state) { UnimplementedInstruction(state); }
void Swap(InterpreterState *state) { UnimplementedInstruction(state); }
void ClearStack(InterpreterState *state) { UnimplementedInstruction(state); }
// Stack Stack Manipulation
void BeginBlock(InterpreterState *state) { UnimplementedInstruction(state); }
void EndBlock(InterpreterState *state) { UnimplementedInstruction(state); }
void StackUnderStack(InterpreterState *state) { UnimplementedInstruction(state); }
// Funge-Space Storage
void Get(InterpreterState *state) { UnimplementedInstruction(state); }
void Put(InterpreterState *state) { UnimplementedInstruction(state); }
// Standard Input/Output
void OutputDecimal(InterpreterState *state) { UnimplementedInstruction(state); }
void OutputCharacter(InterpreterState *state) { UnimplementedInstruction(state); }
void InputDecimal(InterpreterState *state) { UnimplementedInstruction(state); }
void InputCharacter(InterpreterState *state) { UnimplementedInstruction(state); }
// File Input/Output
void InputFile(InterpreterState *state) { UnimplementedInstruction(state); }
void OutputFile(InterpreterState *state) { UnimplementedInstruction(state); }
// System
void Execute(InterpreterState *state) { UnimplementedInstruction(state); }
void GetSysInfo(InterpreterState *state) { UnimplementedInstruction(state); }
// Fingerprints
void CustomInstruction(InterpreterState *state) { UnimplementedInstruction(state); }
void LoadSemantics(InterpreterState *state) { UnimplementedInstruction(state); }
void UnloadSemantics(InterpreterState *state) { UnimplementedInstruction(state); }
// Concurrent Funge-98
void Split(InterpreterState *state) { UnimplementedInstruction(state); }




void applyDeltaToIp(InterpreterState *state)
{
	state->delta.dx < 0 && Left(&state->ip);
	state->delta.dx > 0 && Right(&state->ip);
	state->delta.dy < 0 && Up(&state->ip);
	state->delta.dy > 0 && Down(&state->ip);
}

void runInterpreterStep(InterpreterState *state)
{
	if (state->errorFlag)
		return;
	applyDeltaToIp(state);

	Mutator jmp[] = {
		[0 ... 255] = &IrrecoverableError,
		[' '] = &DoNothing,
		['!'] = &LogicalNot,
		['"'] = &ToggleStringmode,
		['#'] = &Trampoline,
		['$'] = &Pop,
		['%'] = &Remainder,
		['&'] = &InputDecimal,
		['\'']= &FetchCharacter,
		['('] = &LoadSemantics,
		[')'] = &UnloadSemantics,
		['*'] = &Multiply,
		['+'] = &Add,
		[','] = &OutputCharacter,
		['-'] = &Subtract,
		['.'] = &OutputDecimal,
		['/'] = &Divide,
		['0' ... '9'] = &Push,
		['a' ... 'f'] = &Push,
		[':'] = &Duplicate,
		[';'] = &JumpOver,
		['<'] = &GoWest,
		['='] = &Execute,
		['>'] = &GoEast,
		['?'] = &GoRandom,
		['@'] = &Stop,
		['A' ... 'Z'] = &CustomInstruction,
		['['] = &TurnLeft,
		['\\'] = &Swap,
		[']'] = &TurnRight,
		['^'] = &GoNorth,
		['_'] = &EastWestIf,
		['`'] = &GreaterThan,
		['g'] = &Get,
		['h'] = &GoHigh,
		['i'] = &InputFile,
		['j'] = &JumpForward,
		['k'] = &Iterate,
		['l'] = &GoLow,
		['m'] = &HighLowIf,
		['n'] = &ClearStack,
		['o'] = &OutputFile,
		['p'] = &Put,
		['q'] = &Quit,
		['r'] = &Reverse,
		['s'] = &StoreCharacter,
		['t'] = &Split,
		['u'] = &StackUnderStack,
		['v'] = &GoSouth,
		['w'] = &Compare,
		['x'] = &AbsoluteDelta,
		['y'] = &GetSysInfo,
		['z'] = &DoNothing,
		['{'] = &BeginBlock,
		['|'] = &NorthSouthIf,
		['}'] = &EndBlock,
		['~'] = &InputCharacter,
	};

	auto offset = indexToOffset(state->ip);
	jmp[offset](state);
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
