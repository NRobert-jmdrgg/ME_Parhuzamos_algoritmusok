#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 0;

void *routine();


int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    // race condition
    printf("value of x: %d", x);
    return 0;
}

void *routine()
{
    for (size_t i = 0; i < 1000000; i++)
    {
        x++;
    }
    
}

