#ifndef PA08_H
#define PA08_H		 

#define ASCII_SIZE 256

typedef struct TreeNode {
   int label;				//ascii value
   long count;				//frequency
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
   TreeNode * ptr;
   struct ListNode *next;
} ListNode;

void buildHuffmanTree(ListNode * head);

ListNode * buildParent(ListNode * head, ListNode * First, ListNode * Second);

void insert(ListNode * head, ListNode * newNode);

void printHuffmanTree(ListNode * head, FILE * fptr);

void traverse(TreeNode * root, char * binarypath, int index, char direction, FILE * fptr);

void freeHuffmanTree(TreeNode * root);

#endif
