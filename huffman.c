#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "list.h"
#include "helper.h"

void buildHuffmanTree(ListNode * head)
{
	while(head->next != NULL)
	{

	ListNode * First = head->next;		
	ListNode * Second = First->next;		

	ListNode * parent = buildParent(head, First, Second);

	insert(head, parent);
	
	}
}

ListNode * buildParent(ListNode * head, ListNode * First, ListNode * Second)		//build parent tree node and its ListNode type
{
	ListNode * root = malloc(sizeof(ListNode));
	TreeNode * parent = buildTreeNode((First->ptr->count) + (Second->ptr->count), -1);
 
	parent->left = First->ptr;	//assign left leaf node to parent
	parent->right  = Second->ptr;	//assign right leaf node

	root->ptr = parent;
	root->next = NULL;

	head->next = Second->next;
	free(First);
	free(Second);

	return root;
}

void insert(ListNode * head, ListNode * newNode)
{
	if (head->next == NULL)		//free all list nodes and head contains the root of binary tree
	{
		head->ptr = newNode->ptr;
		free(newNode);
		return;
	}

	ListNode * prev = NULL;
	ListNode * curr = head->next;

	while(curr != NULL)
	{
		if (curr->ptr->count > newNode->ptr->count)	//compare frequncy
		{
			if (curr == head->next)			//insert head
			{
				newNode->next = curr;
				head->next = newNode;
				return;
			}
			else					//insert middle
			{
				newNode->next = curr;
				prev->next = newNode;
				return;
			}
		}

		prev = curr;
		curr = curr->next;
	}

	prev->next = newNode;		//insert tail
	return;
}
		
void printHuffmanTree(ListNode * head, FILE * fptr)		
{
	char *  binarypath = (char *) malloc (sizeof(char) * 257);
	
	traverse(head->ptr, binarypath, 0, '!', fptr);
	free(binarypath);		
}

void traverse(TreeNode * root, char * binarypath, int index, char direction, FILE * fptr)
{

	binarypath[index] = direction;
	index++;

	if(isAscii(root->label))	//valid ascii value, print binary to file
	{
		fprintf(fptr, "%c:", (char)(root->label));
		int i;
		for(i=1; i < index;i++)
		{
			fprintf(fptr, "%c", binarypath[i]);
		}
		fprintf(fptr, "\n");
	}
	else
	{
		traverse(root->left, binarypath, index, '0', fptr);
		traverse(root->right, binarypath, index, '1', fptr);
	}
		
}

void freeHuffmanTree(TreeNode * root)
{
	
	if(root->left == NULL && root->right == NULL)
	{
		free(root);
	}
	else
	{
		freeHuffmanTree(root->left);
		freeHuffmanTree(root->right);
		free(root);
	}
}













