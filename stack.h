#pragma once
#include <stdint.h>

typedef uint8_t stack_type;

struct Stack;

typedef struct Stack {
	stack_type value;
	struct Stack *previous;
} Stack;

Stack empty();

bool isEmpty(Stack *stack);
Stack empty();
Stack push(stack_type value);
Stack pop();
Stack emptyLinked(uint16_t size);

