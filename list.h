#ifndef LIST_H
#define LIST_H
#include "huffman.h"

TreeNode * buildTreeNode(long frequency, int ascii);

ListNode * buildListNode(long frequency, int ascii);

ListNode * createList(long * asciicount);

void addNode(ListNode * head, ListNode * newNode);

void printList(ListNode * head, FILE * fptr);

void freeList(ListNode *head);

#endif
