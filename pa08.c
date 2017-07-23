#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "list.h"
#include "helper.h"

int main(int argc, char **argv)
{
	if (argc != 4) 
	{
		printf("Not enough arguments");
		return EXIT_FAILURE;
	}

	FILE * inFile = fopen(argv[1], "r");

	if (inFile == NULL) 
	{
		fprintf(stderr, "can't open the input file.  Quit.\n");
		return EXIT_FAILURE;
   	}
   
	long * asciiCount = countLetters(inFile);		//read and count the occurrences of characters

	fclose(inFile);
	
	if (asciiCount == NULL)
	{
		fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
		return EXIT_FAILURE;
	}

	FILE * output1 = fopen(argv[2], "w");
	
	ListNode * head = createList(asciiCount);

	free(asciiCount);

	printList(head, output1);
	
	fclose(output1);

	FILE * output2 = fopen(argv[3], "w");
	
	buildHuffmanTree(head);

	printHuffmanTree(head, output2);

	fclose(output2);
	
	freeHuffmanTree(head->ptr);
	free(head);

	return 0;
}



