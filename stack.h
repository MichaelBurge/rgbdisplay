#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t stack_type;

struct Stack;

typedef struct Stack {
	stack_type value;
	struct Stack *previous;
	struct Stack *next;
} Stack;

Stack empty();

bool isEmpty(Stack *stack);
Stack empty();
Stack push(Stack *stack, stack_type value);
Stack pop(Stack *stack);
Stack *emptyLinked(uint16_t size);

