#include "befunge.h"

int main()
{
	InterpreterState state = emptyInterpreter();
	uint8_t instructions[36] = {
		"X>v>vX"
		"v < < "
		">   ^ "
		"??????"
		"??????"
		"X????X"
	};
	state.instructions = instructions;
	runInterpreterStep(&state);
	return 0;
}
