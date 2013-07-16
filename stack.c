#include "stack.h"
#include <stdlib.h>

bool   isEmpty(Stack *stack) { return stack->previous == 0 }
Stack  empty() { return {.value = 0, .previous = 0 } }
Stack  push(Stack stack, stack_type value) { return {.value = value, .previous = stack } }
Stack  pop(Stack stack) { return stack.previous }
Stack* emptyLinked(uint16_t size) {
	Stack *ret = malloc(sizeof(Stack) * size), *iter = ret;
	while (size --> 0) iter++, iter->previous = iter-1;
	return *ret;
}
