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
	bool hrefs_used[size];

	for (int i = 0; i < size; i++) {
		token_hrefs[i] = NULL;
		hrefs_used[i] = false;
	}

	for (int i = 2; i < size; i++) {
		Exptree *tmp_left = NULL;
		Exptree *tmp_right = NULL;

		if (token_is_operator(arr_token, i)) {
			int pos = i - 1;
			//printf("---\n");
			printf("%d\n", pos);
			if (token_hrefs[pos] != NULL) {
				tmp_right = token_hrefs[pos];
				hrefs_used[pos] = true;
				if (token_hrefs[pos - 1] == NULL)
					pos -= 3;
				else
					pos--;
			} else {
				tmp_right = exptree_create(token_get_by_position(arr_token, pos), NULL, NULL);
				pos--;
			}
			printf("%d\n", pos);
			printf("----------\n");

			while (hrefs_used[pos]) {
				if (token_hrefs[pos - 1] == NULL)
					pos -= 3;
				else
					pos--;
			}

			if (token_hrefs[pos] != NULL) {
				tmp_left = token_hrefs[pos];
				hrefs_used[pos] = true;
			}
			else
				tmp_left = exptree_create(token_get_by_position(arr_token, pos), NULL, NULL);

			Exptree *tmp = exptree_create(token_get_by_position(arr_token, i), tmp_left, tmp_right);
			token_hrefs[i] = tmp;
			root = tmp;
			exptree_print(root, 0);
			printf("==========\n");
		}
	}
	return root;
}

void exptree_print(Exptree *root, int lvl)
{
	if (root == NULL) {
		printf("Tree is empty\n");
		return;
	}
	for (int i = 0; i < lvl; i++)
		printf("  ");
	token_print_value(root->value, 0);
	printf("\n");
	if (root->left != NULL)
		exptree_print(root->left, lvl + 1);
	if (root->right != NULL)
		exptree_print(root->right, lvl + 1);
}
/*bool exptree_is_empty(Exptree *exptree) {

}*/
