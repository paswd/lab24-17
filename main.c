#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "exptree.h"
#include "stack.h"
#include "basfunc.h"
#include "token.h"

#define STACK_EMPTY 	-9000000000000000000

int main(void)
{

	char *str = get_string();
	int token_size;
	Token *token = convert_string_to_tokens(str, &token_size);
	free(str);
	str = NULL;

	//printf("%d\n", token_size);
	//token_arr_print(token, token_size);

	int rpn_size;
	Token *rpn = token_convert_to_rpn(token, token_size, &rpn_size);
	token_destroy(&token);

	printf("%d\n", rpn_size);
	token_arr_print(rpn, rpn_size);

	token_destroy(&rpn);

	return 0;
}