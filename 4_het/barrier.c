#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_barrier_t barrier;

void *routine(void *arg);

int main(int argc, char const *argv[])
{
    pthread_t th[10];
    
    pthread_barrier_init(&barrier, NULL, 7);

    for (size_t i = 0; i < 10; i++)
    {
        pthread_create(&th[i], NULL, &routine, NULL);
    }

    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(th[i], NULL); 
    }
    
    pthread_barrier_destroy(&barrier);

    return 0;
}

void *routine(void *arg)
{
    while (1)
    {
        printf("Waiting at the barrier\n");
        sleep(1);
        pthread_barrier_wait(&barrier);
        printf("passed the barrier\n");
    }
}