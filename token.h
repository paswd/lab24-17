#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <stdbool.h>
#include "basfunc.h"
#include "stack.h"

//typedef long long Item;

typedef struct _token Token;

Token *token_copy(Token *token);
void stack_print_chars(Stack *stack);
Token *convert_string_to_tokens(char *str, int *length);
void token_create(Token **token, Item value, bool is_operator, bool is_numeral);
void token_destroy(Token **arr);
void token_arr_print(Token *arr, int size);
Item token_getvalue(Token *arr, int pos);
Token *token_get_by_position(Token *arr, int pos);
void token_print_value(Token *arr, int pos);
Token *token_convert_to_rpn(Token *arr, int size, int *new_size);
bool token_is_operator(Token *arr, int num);
bool token_is_numeral(Token *arr, int num);

#endif
