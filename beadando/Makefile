CC = gcc

FILES = ./src/wordcount_multithreaded.c

OUT = ./bin/wordcount_multithreaded

INCLUDE =  -lpthread -lm -fopenmp

FLAGS = -Wall -Wextra -pedantic -Wfatal-errors

ARGS = test.txt lorem

all:
	$(CC) $(FLAGS) $(FILES) $(INCLUDE) -o $(OUT) && $(OUT) $(ARGS) 
	
	