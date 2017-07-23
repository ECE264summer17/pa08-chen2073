SOURCES=helper.c huffman.c list.c pa08.c
HEADERS=helper.h huffman.h list.h
PROGRAM=pa08
FLAGS=-g -std=c99 -Wall -Werror -Wvla -Wunreachable-code
OBJ = pa08.o helper.o huffman.o list.o

all: $(OBJ)
	gcc $(FLAGS) -o $(PROGRAM) $(OBJ)

pa08.o: pa08.c huffman.h list.h helper.h
	gcc -c pa08.c

helper.o: helper.c huffman.h helper.h
	gcc -c helper.c

huffman.o: huffman.c huffman.h list.h helper.h
	gcc -c huffman.c

list.o: list.c list.h huffman.h
	gcc -c list.c

clean:
	rm $(OBJ)
