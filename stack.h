#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
//#include "exptree.h"
#include "basfunc.h"

//typedef long long Item;

typedef struct _stack_node StackNode;
typedef struct _stack Stack;

Stack* stack_create(void);
void stack_destroy(Stack **stack);
void stack_push(Stack *stack, Item value);
Item stack_pop(Stack *stack);
Item stack_top(Stack *stack);
bool stack_is_empty(Stack *stack);
int stack_depth(Stack *stack);
void stack_print(Stack *stack);

#endif
