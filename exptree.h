#ifndef _EXPTREE_H_
#define _EXPTREE_H_

#include <stdbool.h>
#include "token.h"
#include "basfunc.h"

//typedef long long Item;

typedef struct _exptree Exptree;

Exptree *exptree_create(Token *value, Exptree *left, Exptree *right, bool is_operation);
void exptree_destroy(Exptree **root);
//Exptree *exptree_generate_from_rpn(Token *arr_token, int size);

#endif
