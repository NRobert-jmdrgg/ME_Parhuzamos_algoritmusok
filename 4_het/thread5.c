#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t mut;

void *routine();


int main(int argc, char const *argv[])
{
    pthread_t threads[4];

    pthread_mutex_init(&mut, NULL);

    for (size_t i = 0; i < 4; i++)
    {
        pthread_create(threads + i, NULL, &routine, NULL);
        printf("thread %d started\n", i);
        
    }

    for (size_t i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
        printf("thread %d stopped\n", i);
    }
    
    
    
    pthread_mutex_destroy(&mut);
    printf("value of x: %d", x);
    return 0;
}

void *routine()
{
    for (size_t i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mut);
        x++;
        pthread_mutex_unlock(&mut);
    }
    
}

