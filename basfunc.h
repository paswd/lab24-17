#ifndef _BASFUNC_H_
#define _BASFUNC_H_

#include <stdbool.h>

typedef long long Item;

char *get_string(void);
char *string_copy(char *str);
bool is_num(char sym);
bool is_letter(char sym);
int char_to_int(char num);
char int_to_char(int num);
int get_operation_priority(char op);
void add_item_to_string(char *str, Item num);
void add_sign_to_string(char *str, char sign);

#endif
