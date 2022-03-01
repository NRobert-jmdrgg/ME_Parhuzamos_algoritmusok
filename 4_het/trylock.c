#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mut;

void *routine(void *arg);

int main(int argc, char const *argv[])
{
    pthread_t th[4];
    pthread_mutex_init(&mut, NULL);

    for (size_t i = 0; i < 4; i++)
    {
        pthread_create(&th[i], NULL, &routine, NULL);
    }

    for (size_t i = 0; i < 4; i++)
    {
        pthread_join(th[i], NULL);
    }
    
    return 0;
}

void *routine(void *arg)
{
    if (pthread_mutex_trylock(&mut) == 0) 
    {
        printf("Hello, lock\n");
        sleep(1);
        pthread_mutex_unlock(&mut);
    }
    else 
    {
        printf("Didn't get lock\n");
    }
    
}