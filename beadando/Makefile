CC = gcc

FILES = ./src/dir_cleaner.c

OUT = ./bin/dir_cleaner

INCLUDE =  -lpthread -lm -fopenmp

FLAGS = -Wall -Wextra -pedantic -Wfatal-errors

ARGS = test.txt lorem

all:
	$(CC) $(FLAGS) $(FILES) $(INCLUDE) -o $(OUT) && $(OUT) 
	
	