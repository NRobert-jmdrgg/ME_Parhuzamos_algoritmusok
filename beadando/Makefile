CC = gcc

FILES = ./src/KMP_multi.c

OUT = ./bin/KMP_multi

INCLUDE =  -lpthread -lm -fopenmp

FLAGS = -Wall -Wextra -pedantic -Wfatal-errors

ARGS = test.txt lorem

all:
	$(CC) $(FLAGS) $(FILES) $(INCLUDE) -o $(OUT) && $(OUT) $(ARGS) 
	
	