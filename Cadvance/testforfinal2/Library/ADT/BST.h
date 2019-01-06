#ifndef __BST_H
#define __BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------Declaraion BEGIN------------------------------------- */

typedef struct BSTNode {
	void *data;
	struct BSTNode *parent;
	struct BSTNode *left;
	struct BSTNode *right;
} BSTNode;

typedef struct {
	BSTNode *root;
	int elementSize;
} BST;

typedef int (*comparator)(void *, void *);

typedef void (*todoBST)(void *);


/*-----------Declaraion END-----------------------------------------*/

BST *newBST(int elementSize) {

	BST *newTree = (BST *) malloc(sizeof(BST));

	newTree->root = NULL;
	newTree->elementSize = elementSize;
	
	return(newTree);
}

BSTNode *makeNewBSTNode(void *data) {

	BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));

	newNode->data = data;
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return(newNode);
}

BSTNode *search(BSTNode *root, void *data, comparator cmp) {

	if (root == NULL) {
		return(NULL);
	}

	if (cmp(root->data, data) == 0) return(root);
	
	if (cmp(root->data, data) == 1)
		return( search(root->left, data, cmp) );
	else
		return( search(root->right, data, cmp) );
}

void insertBST(
			   BSTNode **root,
			   BSTNode *parent,
			   void *data,
			   comparator cmp
			   ) {
   
	if (*root == NULL) {

		BSTNode *newNode = makeNewBSTNode(data);
		newNode->parent = parent;
		*root = newNode;

		return;
	}

	if ( cmp((*root)->data, data) == 1) {
		insertBST( &((*root)->left), *root, data, cmp);
	}
	else {
		insertBST( &((*root)->right), *root, data, cmp);
	}
	
}

int treeSize(BSTNode *root) {
	if (root == NULL) {
		return(0);
	}

	return(treeSize(root->left) + treeSize(root->right) + 1);
}

int treeNumLeaves(BSTNode *root) {

	if (root == NULL) return(0);
	if (root->left == NULL && root->right == NULL) {
		return(1);
	}

	if (root->left != NULL) {
		return(treeNumLeaves(root->left));
	}

	if (root->right != NULL) {
		return(treeNumLeaves(root->right));
	}
}

BSTNode *findMax(BSTNode *root)
{
    if (root == NULL) return(NULL);

    BSTNode *max = root;
    while (max->right != NULL)
        max = max->right;

    return(max);
}

BSTNode *findMin(BSTNode *root)
{
    if (root == NULL) return(NULL);

    BSTNode *min = root;
    while (min->left != NULL)
        min = min->left;

    return(min);
}

/*------- del -------*/

void spliceOut(BSTNode *current_node) {
	
    // if the current node is leaf
    if (current_node->left == NULL && current_node->right == NULL) {
        if (current_node->parent->left == current_node)
            current_node->parent->left = NULL;
        else
            current_node->parent->right = NULL;
    }

	// if the current node has any child
	else if ( (current_node->left == NULL) || (current_node->right == NULL) ) {
		
		if (current_node->left != NULL) {
			if (current_node->parent->left == current_node)
                current_node->parent->left = current_node->left;
            else
                current_node->parent->right = current_node->left;
			
            current_node->left->parent = current_node->parent;
        }
        else {
            if (current_node->parent->left == current_node)
                current_node->parent->left = current_node->right;
            else
                current_node->parent->right = current_node->right;
			
            current_node->right->parent = current_node->parent;
        }
    }
	
    free(current_node);
	
    return;
}

BSTNode *findSuccessor(BSTNode *currentNode) {

	BSTNode *succ = NULL;
    if (currentNode->right != NULL) {
        succ = findMin(currentNode->right);
	}
   	else {
		
        if (currentNode->parent) {
			if (currentNode->parent->left == currentNode)
                succ = currentNode->parent;
            else {
                currentNode->parent->right = NULL;
                succ = findSuccessor(currentNode->parent);
                currentNode->parent->right = currentNode;
            }
        }
	}
	return(succ);
}
	
void del(BSTNode **root, void *data, comparator cmp) {

	// the tree is empty
	if (*root == NULL) {
		return;
	}
	else if ( cmp((*root)->data, data) == 1 ) {
		del( &((*root)->left), data, cmp);
	}
	else if ( cmp((*root)->data, data) == -1 ) {
		del( &((*root)->right), data, cmp);
	}
	else {
		BSTNode *delNode = *root;

		// case 1: node is a leaf (no descendants)
		if ((delNode->left == NULL) && (delNode->right == NULL)) {
			// if the delNode is a left child
			if (delNode->parent->left == delNode) {
				delNode->parent->left = NULL;
				free(delNode);
				printf("Node deld!\n");
				return;
			}

			// if the delNode is a right child
			else if (delNode->parent->right == delNode) {
				delNode->parent->right = NULL;
				free(delNode);
				printf("Node deld!\n");
				return;
			}
		}
		
		// case 2: node has one child
		else if ((delNode->left == NULL) || (delNode->right == NULL) ) {
			// if the delNode has left child
			if (delNode->left != NULL) {
				// if the delNode is a left child
				if (delNode->parent->left == delNode) {
					delNode->left->parent = delNode->parent;
					delNode->parent->left = delNode->left;
					free(delNode);
					printf("Node deld!\n");
					return;
				}
				
				// if the delNode is a right child
				else if (delNode->parent->right == delNode) {
					delNode->left->parent = delNode->parent;
					delNode->parent->right = delNode->left;
					free(delNode);
					printf("Node deld!\n");
					return;
				}
				// otherwise the delNode is the root
				else {
					delNode->data = delNode->left->data;
					delNode->left = delNode->left->left;
					delNode->right = delNode->left->right;
					free(delNode);
					printf("Node deld!\n");
				}
			}
			
			// if the delNode has right child
			else {
				// if the delNode is left child
				if (delNode->parent->left == delNode) {
					delNode->right->parent = delNode->parent;
					delNode->parent->left = delNode->right;
					free(delNode);
					printf("Node deld!\n");
					return;
				}
				
				// if the delNode is right child
				else if (delNode->parent->right == delNode) {
					delNode->right->parent = delNode->parent;
					delNode->parent->right = delNode->right;
					free(delNode);
					printf("Node deld!\n");
					return;
				}
				// otherwise the delNode is the root
				else {
					delNode->data = delNode->right->data;
					delNode->left = delNode->right->left;
					delNode->right = delNode->right->right;
					return;
				}
			}
		}
		
		// case 3: the delNode has both child
		else {
			BSTNode *succ = findSuccessor(delNode);
			delNode->data = succ->data;
			spliceOut(succ);
			printf("Node deld!\n");
		}
	}	
}
/*---del end-------- */
/*---------------------- tree traversal ----------------------------*/

void inorder(BSTNode *root, todoBST toDo) {

	if (root == NULL) return;

	inorder(root->left, toDo);
	toDo(root->data);
	inorder(root->right, toDo);
}

void postorder(BSTNode *root, todoBST toDo) {

	if (root == NULL) return;
	
	postorder(root->left, toDo);
	postorder(root->right, toDo);
	toDo(root->data);
}

void preorder(BSTNode *root, todoBST toDo) {
	if (root == NULL) return;

	toDo(root->data);
	preorder(root->left, toDo);
	preorder(root->right, toDo);
}

/*---------------------------------------------------------------------*/

void freeBST(BSTNode *root) {

	if (root == NULL) return;
	
	freeBST(root->left);
	freeBST(root->right);
	free(root);
}

#include "printTreeASCII.h"

#endif
