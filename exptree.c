#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "exptree.h"
#include "stack.h"
#include "token.h"

/*typedef enum {
	NUMERAL,
	VARIABLE,
	EXPRESSION
} Category;*/

struct _exptree {
	//Item value;
	Token *value;
	//Category cat;
	bool is_operation;
	Exptree *left;
	Exptree *right;
};

//Exptree *exptree_create(char *str)
Exptree *exptree_create(Token *token, Exptree *left, Exptree *right)
{
	Exptree *nw = (Exptree *) calloc(1, sizeof(Exptree));
	nw->value = token_copy(token);
	nw->left = left;
	nw->right = right;
	nw->is_operation = token_is_operator(nw);
	return nw;
}
void exptree_destroy(Exptree **root)
{
	if ((*root)->left != NULL) 
		exptree_destroy(&((*root)->left));
	(*root)->left = NULL;

	if ((*root)->right != NULL) 
		exptree_destroy(&((*root)->right));
	(*root)->right = NULL;

	free(*root);
	*root = NULL;
}

/*Exptree *exptree_generate_from_rpn(Token *arr_token, int size)
{
	Exptree *root = NULL;
	Exptree *token_hrefs[size];

	for (int i = 0; i < size; i++) {
		token_hrefs[i] = NULL;
	}

	for (int i = 1; i < size; i++) {
		Exptree *tmp_left = NULL;
		Exptree *tmp_right = NULL;
		if (i == 1 && token_getvalue(arr_token, 1) == '-') {
			Token zero;
			zero.value = 0;
			zero.is_operation = false;
			zero.is_numeral = true;
			tmp_left = exptree_create(zero, NULL, NULL, false);
			tmp_right = exptree_create(arr_token[0], NULL, NULL, false);
			root = exptree_create(arr_token[1], tmp_left, tmp_right, true);
			token_hrefs[1] = root;
			continue;
		}

		if (token_is_operator(arr_token, i)) {
			Exptree *tmp = exptree_create(arr_token[i], NULL, NULL, true);
			token_hrefs[i] = tmp;

			int pos = i - 1;
			if (token_hrefs[pos] != NULL) {
				tmp->left = token_hrefs[pos];
			}

		}
	}
	return root;
}*/

/*void exptree_print(Exptree *root, int lvl)
{
	return;
}*/
/*bool exptree_is_empty(Exptree *exptree) {

}*/
