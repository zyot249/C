#ifndef __AVLTREE_H
#define __AVLTREE_H

//  Randomized Binary Search Tree (Treap)

#include <stdio.h>
#include <stdlib.h>

typedef struct Tree_node {
	void *key;
	void *payload;
	int height;
	struct Tree_node *left;
	struct Tree_node *right;
} Tree_node;

typedef int (* Comparator_key)(void *, void *);
typedef void (* ToDo)(Tree_node *);


/************* tree traversal ****************************************/

void pre_order(Tree_node *root, ToDo todo) {
	if (root != NULL) {
		todo(root);
		pre_order(root->left, todo);
		pre_order(root->right, todo);
	}
	return;
}

/****************************************************************************/

/**************** BEGIN insert and delete node ******************************/

int max(int a, int b) {
	return a > b ? a : b;
}

int height(Tree_node *root) {
	if (root == NULL) {
		return 0;
	}
	
	return root->height;
}

Tree_node *new_tree_node(void *key, void *payload) {
	Tree_node *new_node = (Tree_node *)malloc(sizeof(Tree_node));

	new_node->key = key;
	new_node->payload = payload;
	new_node->height = 1; // new node is initially added at leaf
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

Tree_node *right_rotate(Tree_node *y) {
	Tree_node *x = y->left;
	Tree_node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

Tree_node *left_rotate(Tree_node *x) {
	Tree_node *y = x->right;
	Tree_node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

int get_balance_factor(Tree_node *root) {
	if (root == NULL) {
		return 0;
	}
	return height(root->left) - height(root->right);
}

Tree_node *rebalance_tree(Tree_node *root, void *key, Comparator_key cmp_func) {

	int root_balance_factor = get_balance_factor(root);

	/* left left case */
	if (root_balance_factor > 1 && cmp_func(root->left->key, key) > 0) {
		return right_rotate(root);
	}

	/* right right case */
	if (root_balance_factor < -1 && cmp_func(root->right->key, key) < 0) {
		return left_rotate(root);
	}

	/* left right case */
	if (root_balance_factor > 1 && cmp_func(root->left->key, key) < 0) {
		root->left = left_rotate(root->left);
		return right_rotate(root);
	}

	/* right left case */
	if (root_balance_factor < -1 && cmp_func(root->right->key, key) > 0) {
		root->right = right_rotate(root->right);
		return left_rotate(root);
	}

	return root;
}

void update_tree_hight(Tree_node *root) {
	root->height = 1 + max(height(root->left), height(root->right));
	return;
}


Tree_node *_insert(Tree_node *root, void *key, void *payload, Comparator_key cmp_func) {
	
	if (root == NULL) {
		return new_tree_node(key, payload);
	}

	if (cmp_func(root->key, key) > 0) {
		root->left = _insert(root->left, key, payload, cmp_func);
	}
	else if (cmp_func(root->key, key) < 0) {
		root->right = _insert(root->right, key, payload, cmp_func);
	}
	else { // Equal key is not allow in BST
		return root;
	}

	update_tree_hight(root);
	return rebalance_tree(root, key, cmp_func);
}

void insert(Tree_node **root, void *key, void *payload, Comparator_key cmp_func) {
	*root = _insert(*root, key, payload, cmp_func);
	return;
}


Tree_node *min_node(Tree_node *root) {
	Tree_node *current = root;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

Tree_node *_delete_node(Tree_node *root, void *key, Comparator_key cmp_func) {
	if (root == NULL) return NULL;

	if (cmp_func(root->key, key) > 0) {
		root->left = _delete_node(root->left, key, cmp_func);
	}
	else if (cmp_func(root->key, key) < 0) {
		root->right = _delete_node(root->right, key, cmp_func);
	}
	else {
		if (root->left == NULL || root->right == NULL) {
			Tree_node *temp_node = root->left
				? root->left
				: root->right;

			if (temp_node == NULL) {
				temp_node = root;
				root = NULL;
			} else {
				*root = *temp_node;
			}
			free(temp_node);
		}
		else {
			Tree_node *temp_node = min_node(root->right);
			root->key = temp_node->key;
			root->right = _delete_node(root->right, temp_node->key, cmp_func);
		}
	}
	
	if (root == NULL) return NULL;
	update_tree_hight(root);
	return rebalance_tree(root, key, cmp_func);
}

void delete_node(Tree_node **root, void *key, Comparator_key cmp_func) {
	*root = _delete_node(*root, key, cmp_func);
	return;
}

/************************** END insert and delete node ************************/

#endif
