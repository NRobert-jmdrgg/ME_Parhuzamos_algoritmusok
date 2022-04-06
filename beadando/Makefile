
single:
	gcc -Wall -Wextra -pedantic -Wfatal-errors ./src/wordcount_singlethreaded.c -lpthread -lm -o ./bin/wordcount_singlethreaded && ./bin/wordcount_singlethreaded test.txt lorem

multi:
	gcc -Wall -Wextra -pedantic -Wfatal-errors ./src/wordcount_multithreaded.c -lpthread -lm -o ./bin/wordcount_multithreaded && ./bin/wordcount_multithreaded test.txt lorem

run_single:
	./bin/wordcount_singlethreaded test.txt lorem

run_multi:
	./bin/wordcount_multithreaded test.txt lorem