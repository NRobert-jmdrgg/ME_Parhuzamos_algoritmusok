CC = gcc

FILES = ./src/sudoku.c

OUT = ./bin/sudoku

INCLUDE =  -lpthread -lm -fopenmp

FLAGS = -Wall -Wextra -pedantic -Wfatal-errors

ARGS = test.txt lorem

all:
	$(CC) $(FLAGS) $(FILES) $(INCLUDE) -o $(OUT) && $(OUT) $(ARGS) 
	
	