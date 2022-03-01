#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg);

int main(int argc, char const *argv[])
{
    pthread_t th[2];
    size_t i;
    for (i = 0; i < 2; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i * 5;
        pthread_create(&th[i], NULL, &routine, a);        
    }

    int *res;
    int sum = 0;
    for (i = 0; i < 2; i++)
    {
        
        pthread_join(th[i], (void **) &res);
        sum += *res;
        
    }
    printf("sum: %d", sum);
    free(res);

    return 0;
}

void *routine(void *arg)
{
    int index = *(int *)arg;
    int sum = 0;
    
    for (size_t i = 0; i < 5; i++)
    {
        sum += primes[index + i];
    }

    printf("routine sum: %d\n", sum);
    
    *(int *)arg = sum;

    return arg;
}