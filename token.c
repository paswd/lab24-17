#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "basfunc.h"
#include "token.h"

#define STACK_EMPTY 	-9000000000000000000

struct _token {
	Item value;
	bool is_operator;
	bool is_numeral;
};

Token *token_copy(Token *token)
{
	Token *nw = (Token *) calloc(1, sizeof(Token));
	nw->value = token->value;
	nw->is_operator = token->is_operator;
	nw->is_numeral = token->is_numeral;
	return nw;
}

void stack_print_chars(Stack *stack)
{
	if (stack_is_empty(stack))
		return;
	Item value = stack_pop(stack);
	stack_print_chars(stack);
	stack_push(stack, value);
	printf("%c ", (char) value);
}

Token *convert_string_to_tokens(char *str, int *length)
{
	//printf("Function enter\n");
	int size = strlen(str);
	printf("%d\n", size);
	Token *token_arr = (Token *) calloc(size * 2, sizeof(Token));
	for (int i = 0; i < size; i++)
		token_arr[i].value = 0;

	int pos = 0;
	bool is_operand_passed = false;
	bool set_closing = false;
	int prev = 0;
	for (int i = 0; i < size; i++) {
		if (str[i] == ' ')
			continue;
		//printf("For: step %d\n", i);
		if (is_letter(str[i])) {
			token_arr[pos].is_numeral = false;
			token_arr[pos].is_operator = false;
			token_arr[pos].value = str[i];
			is_operand_passed = true;
			continue;
		}
		if (is_num(str[i])) {
			token_arr[pos].is_numeral = true;
			token_arr[pos].is_operator = false;
			token_arr[pos].value *= 10;
			token_arr[pos].value += char_to_int(str[i]);
			is_operand_passed = true;
			continue;
		}
		if (is_operand_passed) {
			pos++;
			is_operand_passed = false;
		}
		if (set_closing) {
			token_arr[pos].value = ')';
			token_arr[pos].is_numeral = false;
			token_arr[pos].is_operator = true;
			set_closing = false;
			pos++;
		}
		if ((prev == 0 || prev == '(') && str[i] == '-') {
			if (prev == 0) {
				token_arr[pos].value = '(';
				token_arr[pos].is_numeral = false;
				token_arr[pos].is_operator = true;
				set_closing = true;
				pos++;
			}

			token_arr[pos].value = 0;
			token_arr[pos].is_numeral = true;
			token_arr[pos].is_operator = false;
			pos++;
		}

		token_arr[pos].is_numeral = false;
		token_arr[pos].is_operator = true;
		token_arr[pos].value = str[i];
		pos++;
	}
	if (is_operand_passed) {
		pos++;
		is_operand_passed = false;
	}
	/*if (!token_arr[pos].is_operator)
		pos++;*/
	//token_arr[pos - 1].is_last = true;
	token_arr = (Token *) realloc(token_arr, pos * sizeof(Token));
	*length = pos;
	
	//printf("Function out\n");
	return token_arr;
}

void token_create(Token **token, Item value, bool is_operator, bool is_numeral)
{
	if (*token == NULL)
		*token = (Token *) calloc(1, sizeof(Token));
	(*token)->value = value;
	(*token)->is_operator = is_operator;
	(*token)->is_numeral = is_numeral;
}

void token_destroy(Token **arr)
{
	free(*arr);
	*arr = NULL;
}

void token_arr_print(Token *arr, int size)
{
	for (int i = 0; i < size; i++) {
		token_print_value(arr, i);
		//printf(" ");
	}
	printf("\n");
}

Item token_getvalue(Token *arr, int pos)
{
	return (arr + pos)->value;
}
Token *token_get_by_position(Token *arr, int pos)
{
	return arr + pos;
}

void token_print_value(Token *arr, int pos)
{
	if (arr[pos].is_numeral) {
		printf("%lld", arr[pos].value);
	} else {
		printf("%c", (char) arr[pos].value);
	}
}

Token *token_convert_to_rpn(Token *arr, int size, int *new_size)
{
	Token *new_arr = (Token *) calloc(size, sizeof(Token));
	Stack *stack = stack_create();

	int pos = 0;
	for (int i = 0; i < size; i++) {
		/*if (i > 0) {
			printf("Step %d: ", i);
			stack_print_chars(stack);
			printf("\n");
		}*/
		if (!arr[i].is_operator) {
			new_arr[pos] = arr[i];
			pos++;
			continue;
		}


		if (arr[i].value == '(') {
			stack_push(stack, arr[i].value);
			continue;
		}
		if (arr[i].value == ')') {
			while (stack_top(stack) != '(') {
				if (stack_top(stack) == STACK_EMPTY) {
					printf("Invalid expression\n");
					free(new_arr);
					return NULL;
				}
				new_arr[pos].value = stack_pop(stack);
				new_arr[pos].is_numeral = false;
				new_arr[pos].is_operator = true;
				pos++;
			}
			stack_pop(stack);
			continue;
		}

		if (stack_is_empty(stack)) {
			stack_push(stack, arr[i].value);
			continue;
		}
		if (get_operation_priority(stack_top(stack)) == get_operation_priority('+')) {
			if (get_operation_priority(arr[i].value) == 1) {
				new_arr[pos].value = stack_pop(stack);
				new_arr[pos].is_numeral = false;
				new_arr[pos].is_operator = true;
				stack_push(stack, arr[i].value);
				pos++;
				continue;
			}
			if (get_operation_priority(arr[i].value) == get_operation_priority('*')) {
				stack_push(stack, arr[i].value);
				continue;
			}
			if (get_operation_priority(arr[i].value) == get_operation_priority('^')) {
				stack_push(stack, arr[i].value);
				continue;
			}
		}
		if (get_operation_priority(stack_top(stack)) == '*') {
			if (get_operation_priority(arr[i].value) == '+') {
				new_arr[pos].value = stack_pop(stack);
				new_arr[pos].is_numeral = false;
				new_arr[pos].is_operator = true;
				stack_push(stack, arr[i].value);
				pos++;
				continue;
			}
			if (get_operation_priority(arr[i].value) == '*') {
				new_arr[pos].value = stack_pop(stack);
				new_arr[pos].is_numeral = false;
				new_arr[pos].is_operator = true;
				stack_push(stack, arr[i].value);
				pos++;
				continue;
			}
			if (get_operation_priority(arr[i].value) == '^') {
				stack_push(stack, arr[i].value);
				continue;
			}	
		}
		if (get_operation_priority(stack_top(stack)) == '^') {
			if (get_operation_priority(arr[i].value) == '+') {
				new_arr[pos].value = stack_pop(stack);
				new_arr[pos].is_numeral = false;
				new_arr[pos].is_operator = true;
				stack_push(stack, arr[i].value);
				pos++;
				continue;
			}
			if (get_operation_priority(arr[i].value) == '*') {
				new_arr[pos].value = stack_pop(stack);
				new_arr[pos].is_numeral = false;
				new_arr[pos].is_operator = true;
				stack_push(stack, arr[i].value);
				pos++;
				continue;
			}
			if (get_operation_priority(arr[i].value) == '^') {
				new_arr[pos].value = stack_pop(stack);
				new_arr[pos].is_numeral = false;
				new_arr[pos].is_operator = true;
				stack_push(stack, arr[i].value);
				pos++;
				continue;
			}	
		}
		if (stack_top(stack) == '(') {
			stack_push(stack, arr[i].value);
		}
	}

	/*printf("Finish: ");
	stack_print_chars(stack);
	printf("\n");*/

	while (!stack_is_empty(stack)) {
		if (stack_top(stack) == '(') {
			printf("Invalid expression\n");
			free(new_arr);
			return NULL;
		}
		new_arr[pos].value = stack_pop(stack);
		new_arr[pos].is_numeral = false;
		new_arr[pos].is_operator = true;
		pos++;
	}

	*new_size = pos;
	stack_destroy(&stack);
	return new_arr;
}

bool token_is_operator(Token *arr, int pos)
{
	return arr[pos].is_operator;
}
bool token_is_numeral(Token *arr, int pos)
{
	return arr[pos].is_numeral;
}
