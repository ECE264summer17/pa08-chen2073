#include<stdio.h>
#include<stdlib.h>
#include "huffman.h"
#include "helper.h"

long *countLetters(FILE *fp)		/* count the occurrences in a file */
{
	long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
	
	if (asciiCount == NULL)
	{
		return NULL;
	}
	
	int ch;
	for (ch = 0; ch < ASCII_SIZE; ch++) 
	{
		asciiCount[ch] = 0;
	}
	
	fseek(fp, 0, SEEK_SET);
	
	while ((ch = fgetc(fp)) != EOF) 
	{
		asciiCount[ch] += 1;
	}
	return asciiCount;
}

bool isAscii(int label)		//valid the value wether it is an ascii value
{
	if ((label < ASCII_SIZE) && (label > -1))
	{	
		return true;
	}
	else
	{
		return false;
	}
}
