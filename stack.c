#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "stack.h"
//#include "basfunc.h"

#define STACK_NO_ERRORS              0 
#define STACK_STACK_OVERFLOW  (1u << 0)
#define STACK_STACK_UNDERFLOW (1u << 1)
#define STACK_EMPTY 	-9000000000000000000

struct _stack_node {
	Item value;
	StackNode *next;
};

struct _stack {
	StackNode *top;
};

Stack *stack_create(void)
{
	Stack *nw = (Stack *) calloc(1, sizeof(Stack));
	nw->top = NULL;
	return nw;
}

void stack_destroy(Stack **stack)
{
	StackNode *node_del = (*stack)->top;
	while (node_del) {
		StackNode *tmp = node_del->next;
		free(node_del);
		node_del = tmp;
	}
	free(*stack);
	*stack = NULL;
}

void stack_push(Stack *stack, Item value)
{
	StackNode *nw = (StackNode *) calloc(1, sizeof(StackNode));
	//printf("PUSH: TRUE\n");
	nw->value = value;
	nw->next = stack->top;
	stack->top = nw;
}

Item stack_pop(Stack *stack)
{
	if (stack->top == NULL) {
		printf("Stack is empty\n");
		return STACK_EMPTY;
	}
	Item result = stack->top->value;
	StackNode *node_del = stack->top;
	stack->top = stack->top->next;
	free(node_del);
	return result;
}

Item stack_top(Stack *stack)
{
	if (stack_is_empty(stack))
		return STACK_EMPTY;
	return stack->top->value;
}

/*void stack_print_correct(Stack *stack)
{
	StackNode *ths = stack->first;
	while (ths) {
		printf("%lld ", ths->value);
		ths = ths->next;
	}
	printf("\n");
}*/

bool stack_is_empty(Stack *stack)
{
	if (stack->top == NULL)
		return true;
	return false;
}

int stack_depth(Stack *stack)
{
	if (stack_is_empty(stack))
		return 0;

	Item value = stack_pop(stack);
	int res = stack_depth(stack);
	stack_push(stack, value);
	return res + 1;
}
void stack_print(Stack *stack)
{
	if (stack_is_empty(stack))
		return;
	Item value = stack_pop(stack);
	stack_print(stack);
	stack_push(stack, value);
	printf("%lld ", value);
}
