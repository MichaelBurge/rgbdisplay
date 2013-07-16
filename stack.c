#include "stack.h"
#include <stdlib.h>

bool   isEmpty(Stack *stack) { return stack->previous == 0; }
Stack  empty() { Stack ret = {.value = 0, .previous = 0, .next = 0 }; return ret; }
Stack  push(Stack *stack, stack_type value) { return stack->next->value = value, *(stack->next); }
Stack  pop(Stack *stack) { return *(stack->previous); }
Stack* emptyLinked(uint16_t size) {
	Stack *ret = malloc(sizeof(Stack) * size), *iter = ret;
	while (size --> 0) iter->next = ++iter, iter->previous = iter-1;
	return ret;
}
