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
	nw->is_operation = token_is_operator(token, 0);
	return nw;
}
void exptree_destroy(Exptree **root)
{
	free((*root)->value);
	if ((*root)->left != NULL) 
		exptree_destroy(&((*root)->left));
	(*root)->left = NULL;

	if ((*root)->right != NULL) 
		exptree_destroy(&((*root)->right));
	(*root)->right = NULL;

	free(*root);
	*root = NULL;
}

Exptree *exptree_generate_from_rpn(Token *arr_token, int size)
{
	Exptree *root = NULL;
	Exptree *token_hrefs[size];

	for (int i = 0; i < size; i++) {
		token_hrefs[i] = NULL;
	}

	for (int i = 2; i < size; i++) {
		//Exptree *tmp_left = NULL;
		//Exptree *tmp_right = NULL;

		if (token_is_operator(arr_token, i)) {
			Exptree *tmp = exptree_create((arr_token + i), NULL, NULL);
			token_hrefs[i] = tmp;
			root = tmp;

			int pos = i - 1;
			if (token_hrefs[pos] != NULL) {
				tmp->right = token_hrefs[pos];
				pos -= 3;
			} else {
				tmp->right = exptree_create((arr_token + pos), NULL, NULL);
				pos--;
			}

			if (token_hrefs[pos] != NULL) {
				tmp->left = token_hrefs[pos];
			} else {
				tmp->left = exptree_create((arr_token + pos), NULL, NULL);
			}
		}
	}
	return root;
}

/*void exptree_print(Exptree *root, int lvl)
{
	return;
}*/
/*bool exptree_is_empty(Exptree *exptree) {

}*/
