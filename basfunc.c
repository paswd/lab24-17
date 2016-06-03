#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "basfunc.h"

char *get_string(void)
{
	Queue *queue = queue_create();
	Item sym;
	int cnt = 0;
	while ((sym = getchar()) != EOF) {
		if (sym == '\n')
			continue;
		queue_push(queue, sym);
		cnt++;
	}
	char *str = (char *) calloc(cnt, sizeof(char));
	int i = 0;
	while (!queue_is_empty(queue)) {
		str[i] = queue_pop(queue);
		i++;
	}
	queue_destroy(&queue);
	return str;
}

char *string_copy(char *str)
{
	int size = strlen(str);
	char *nw = (char *) calloc(size, sizeof(char));
	for (int i = 0; i < size; i++) {
		nw[i] = str[i];
	}
	return nw;
}

bool is_num(char sym)
{
	if (sym >= '0' && sym <= '9')
		return true;
	return false;
}
bool is_letter(char sym)
{
	if (sym >= 'a' && sym <= 'z')
		return true;
	return false;
}

int char_to_int(char num)
{
	if (is_num(num)) {
		return num - '0';
	}
	return 0;
}
char int_to_char(int num)
{
	return num + '0';
}

int get_operation_priority(char op)
{
	if (op == '^')
		return 3;
	if (op == '*' || op == '/')
		return 2;
	if (op == '+' || op == '-')
		return 1;
	return 0;
}

void add_item_to_string(char *str, Item num)
{
	int size = strlen(str);
	Stack *stack = stack_create();
	int cnt = 0;
	while (num > 0) {
		stack_push(stack, num % 10);
		num /= 10;
		cnt++;
	}
	printf("%c\n", str[1]);
	str = (char *) realloc((void *) str, (size + cnt) * sizeof(char));
	//printf("Control\n");
	while (!stack_is_empty(stack)) {
		str[size] = int_to_char(stack_pop(stack));
	}
	stack_destroy(&stack);
}
void add_sign_to_string(char *str, char sign)
{
	int size = strlen(str);
	str = (char *) realloc((void *) str, (size + 1) * sizeof(char));
	str[size] = sign;
	printf("Func: out\n");
}

/*int converting_sort_station(Stack *stack, char *in, char *out)
{
	int num_tmp = 0;
	int pos = 0;
	while (str[pos] != EOF && str[pos] != ')') {
		if (is_num(str[pos])) {
			num_tmp *= 10;
			num_tmp += char_to_int(str[pos]);
		} else if (is_letter(str[pos])) {
			num_tmp = str[pos];
		} else {
			add_item_to_string(out, num_tmp);
		}
		pos++;
	}
	if (str[pos] == EOF)
		return -1;
	return pos + 1;
}*/
