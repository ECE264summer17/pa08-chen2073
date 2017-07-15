In this assignment you will design a widely used file compression technique called Huffamn Encoding using binary trees and linked list, which is used in JPEG compression as well as in MP3 audio compression. The algorithm was invented by David A. Huffman in 1952 when he was a Ph.D. student at MIT

# Learning Goals :
In this assignment you will work with
  * Binary trees
  * Linked list

# Background

## ASCII Encoding :
Many programming languages use ASCII (which stands for American Standard Code for Information Interchange) coding to represent characters. In ASCII coding, every character is encoded (represented) with the same number of bits (8-bits) per character. Since there are 256 different values that can be represented with 8-bits, there are potentially 256 different characters in the ASCII character set. 

> With an ASCII encoding (8 bits per character) the 13 character string "go go gophers" requires 104 bits. 
The string "go go gophers" would be written (coded numerically) as 103 111 32 103 111 32 103 111 112 104 101 114 115. This would be written as the following stream of bits (the spaces would not be written, just the 0's and 1's) 
> 1100111 1101111 1100000 1100111 1101111 1000000 1100111 1101111 1110000 1101000 1100101 1110010 1110011

Since there are only eight different characters in "go go gophers", it's possible to use only 3 bits to encode the different characters. By using three bits per character, the string "go go gophers" uses a total of 39 bits instead of 104 bits. 
> Now the string "go go gophers" would be encoded as 0 1 7 0 1 7 0 1 2 3 4 5 6 or, as bits: 
> 000 001 111 000 001 111 000 001 010 011 100 101 110 111 

## Huffman Encoding:

However, even in this improved coding scheme, we used the same number of bits to represent each character, irrespective of how often a character appears in our string. Even more bits can be saved if we use fewer than three bits to encode characters like g, o, and space that occur frequently and more than three bits to encode characters like e, h, p, r, and s that occur less frequently in "go go gophers". *This is the basic idea behind Huffman coding: to use fewer bits for characters that occur more frequently.*

To start, we have to count the occurrence of every character in the string/data that we want to encode. Store occurrence of each character and sort them by their frequency. Begin with a forest of trees. All trees initially consist of one node, with the weight of the tree equal to the weight of the character in the node. Characters that occur most frequently have the highest weights. Characters that occur least frequently have the smallest weights. 

### Example :
We'll use the string `go go gophers` as an example. Initially we have the forest shown below. The nodes are shown with a weight/count that represents the number of times the node's character occurs. We will use sorted linked list whose nodes will point to the respective root tree node. Thus we are representing order of the tree nodes by putting them in an ordered linked list. Each node in the list points to the indivisual tree node. Node pointing to tree node ‘e’ is the head of the list.

![gophers1.jpg](http://i.imgur.com/Edfn4FV.jpg)

We maintain ordered list of items arranged according to their weights. If the two nodes of the list have same weight, a leaf node(associated with an ASCII character) is ordered first. If both nodes are leaf nodes, they are ordered according to their ASCII coding. If both nodes are non-leaf nodes, they are ordered according to the creation times of the nodes.

We always pick the first two items in the list, here, nodes for characters 'e' and 'h'. We create a new tree whose root is weighted by the sum of the weights chosen. Although the newly created node has the same weight as Space, it is ordered after Space in the list because Space is an ASCII character. 
 

![gophers1.jpg](http://i.imgur.com/ESrba5k.jpg)


Choosing the first two (minimal) nodes in the list yields another tree with weight 2 as shown below. There are now six trees in the forest of trees that will eventually build an encoding tree.

![gophers2.jpg](http://i.imgur.com/2Hv3lSC.jpg)

Again we must choose the first two (minimal) nodes in the list. The lowest weight is the 'e'-node/tree with weight equal to 1. There are three trees with weight 2; the one chosen corresponds to an ASCII character because of the way we order the nodes in the list. The new tree has a weight of 3, which will be placed last in the linked list according to our ordering strategy.
 

![gophers3.jpg](http://i.imgur.com/Frm71a5.jpg)


Now there are two trees with weight equal to 2. These are joined into a new tree whose weight is 4. There are four trees left, one whose weight is 4 and three with a weight of 3.


![gophers4.jpg](http://i.imgur.com/8Je9svr.jpg)

The first two minimal (weight 3) trees in the list are joined into a tree whose weight is 6. There are three trees left.


![gophers5.jpg](http://i.imgur.com/XGd3VTS.jpg)

The minimal trees have weights of 3 and 4; these are joined into a tree with weight 7.


![gophers6.jpg](http://i.imgur.com/i8e7HiQ.jpg)


Finally, the last two trees are joined into a final tree whose weight is 13, the sum of the two weights 6 and 7. This tree is the tree we used to illustrate Huffman coding above.

![gophers7.jpg](http://i.imgur.com/ZEQ9KVM.jpg)

To build the code for every character, we start from the root node and travel to every leaf node corresoinding to the character. We denote every left branch as '0' and every right branch as '1'. (Note that '0' and '1' are characters and not bits). We obtain the code for every character according as shown in the table mentioned below :


							| Character | Binary code |
							| --------- |  ---------- |
							|  '  '     |  101        | 
							|  'e'      |  1100       | 
							|  'g'      |  00         |
							|  'h'      |  1101       |
							|  'o'      |  01         | 
							|  'p'      |  1110       |
							|  'r'      |  1111       | 
							|  's'      |  100        |

# What you have to do?

We have provided the starter code that creates an array `asciiCount` of size `ASCII_SIZE` which stores the count of each character at the index of that character’s ASCII value. Value of `ASCII_SIZE` is `256`, defined in `huffman.h` file.

e.g if input file contains character `‘a’` three times and ASCII value of `‘a’` is 97, `asciiCount[97]` will store value `3`.

To create and maintain the sorted list of trees according to their weight, you should implement a linked list, with each node containing the count and and an address that points to the root of binary tree. You should only create tree nodes for characters having non zero count in array `asciiCount`.
We have also given you sample header file which has structure definitions that you will need to implement binary tree and linked list. You have the flexibility, however to design or modify all the files. 

You will have to use bit-wise operations for generating the header information. You should use "`<<`", "`>>`" , "`|`" and "`&`" bit-wise operators and different masks to split the character into chunks of bits desired and shift operators to move the extracted bits to correct positions.

Your program should read an input file (its filename will be provided to the program as `argv[1]`) and produce two output files :
`pa08 inputFileName outputFilename1 outputFilename2 `

**Output file 1** should consist only the characters that appear in the input file and their count, separated by a ‘:’ character. Characters should be sorted in the ascending order according to the count. If two characters have the same number of occurrence, character with the smaller ASCII value should appear first. Do not include any other extra characters. Sample files `gophers_sorted`, `basic_sorted`, `woods_sorted`, `para_sorted` are provided for corresponding input files. 

Input file may contain any character in the ASCII table.
*First character that you see in `basic_sorted` file followed by count 1 is the newline character.* 

**Output file 2** should consist of characters and stream of 0 and 1 (‘0’ and ‘1’ are characters and not bits) corresponding to the Huffman code of the character, seperated by ':' character. Sample files `gophers_huffman`, `basic_huffman`, `woods_huffman`, `para_huffman` are provided for corresponding input files.

## Testing your code
You will need to write your own makefile to implement the code. 
We have provided you with input files and expected files in the inputs and expected folders respectively. 
You should use `‘diff’` command to ensure that there is no difference between the expected files and your output files for the given input files.

## What to turn in :
1. All source files you need to compile and create the executable.
2. A Makefile that specifies a target called `all` that builds producing an executable that must be called `pa08`. Your Makefile should also contain a target called `clean` that removes all intermediate files. Your executable ‘pa08’ should only accept two arguments. E.g.: 

`./pa08 gophers gophers_sorted gophers_huffman 

