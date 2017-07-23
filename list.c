#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "huffman.h"

/** INTERFACE FUNCTIONS **/
TreeNode * buildTreeNode(long frequency, int ascii)
{
	TreeNode * node = malloc(sizeof(TreeNode));	
	
	node->left = NULL;
	node->right = NULL;
	node->label = ascii;	//ascii value
	node->count = frequency;

	return node;
}

ListNode * buildListNode(long frequency, int ascii)
{
	ListNode * node = malloc(sizeof(ListNode));
	TreeNode * tree = buildTreeNode(frequency, ascii);

	node->ptr = tree;
	node->next = NULL;

	return node;
}

void addNode(ListNode * head, ListNode * newNode) 
{	

	if(newNode->ptr->label == 10 && newNode->ptr->count == 1)	//if "\n" frequncy is 1, always goes first
	{	
		if(head->next == NULL)
		{
			head->next = newNode;
			return;
		}
		else
		{
			newNode->next = head->next->next;
			head->next = newNode;
			return;
		}
	}

	if (head->next == NULL)
	{
		head->next = newNode;
		return;
	}

	ListNode * prev = NULL;
	ListNode * curr = head->next;

	while (curr != NULL)
	{
		bool insertHere = false;

		if (curr->ptr->count > newNode->ptr->count)	//compare frequncy
		{			
			 insertHere = true;
		}
		
		else if (curr->ptr->count == newNode->ptr->count)	
		{		    
			if (curr->ptr->label > newNode->ptr->label)	//compare alpabetically
			{		
				insertHere = true;
			}
		}
			
		if (insertHere)
		{	
			if (curr == head->next)		//insert head
			{	
				newNode->next = curr;
				head->next = newNode;
				return;
			}
			else{				//insert in middle
				newNode->next = curr;
				prev->next = newNode;
				return;
			}
		}

		prev = curr;
		curr = curr->next;
	}

	prev->next = newNode;	//insert at tail
	return;	
}

ListNode * createList(long * asciicount)
{
	ListNode * head = malloc(sizeof(ListNode));
	head->ptr = NULL;
	head->next = NULL;

	int i;				//index is also the ascii value
	for(i=0; i < ASCII_SIZE; i++)
	{
		if(asciicount[i] != 0)	//only create nodes for the character has appeared
		{		
			ListNode * newNode = buildListNode(asciicount[i], i);
			addNode(head, newNode);
		}
	}

	return head;
}

void printList(ListNode * head, FILE * fptr) 
{
	ListNode * curr = head->next;
	
	while (curr != NULL) 
	{

		fprintf(fptr, "%c:%ld\n", (char)curr->ptr->label, curr->ptr->count);
		curr = curr->next;
	}
}

void freeList(ListNode * head)	//free entire link list
{
	if (head->next == NULL)
	{
		free(head);
	}
	else
	{
		freeList(head->next);
	}
}
