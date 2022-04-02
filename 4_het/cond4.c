#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

pthread_mutex_t stove_mut[4];
int stove_gas[4] = { 100, 100, 100, 100 };

void *routine(void *arg);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    pthread_t th[10];
    for (size_t i = 0; i < 4; i++)
    {
        pthread_mutex_init(&stove_mut[i], NULL);    
    }
    
    for (size_t i = 0; i < 10; i++)
    {
        pthread_create(&th[i], NULL, &routine, NULL);
    }

    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(th[i], NULL);
    }
    
    for (size_t i = 0; i < 4; i++)
    {
        pthread_mutex_destroy(&stove_mut[i]);
    }

    
    return 0;
}

void *routine(void *arg)
{
    for (size_t i = 0; i < 4; i++)
    {
        if ( pthread_mutex_trylock(&stove_mut[i]) == 0 )
        {
            int gas_needed = rand() % 20;
            if (stove_gas[i] - gas_needed < 0)
            {
                printf("No more gas, going home.\n");
            }
            else
            {
                stove_gas[i] -= gas_needed;
                usleep(500000);
                printf("Fuel left %d\n", stove_gas[i]);
            }
            pthread_mutex_unlock(&stove_mut[i]);
            break;
        } 
        else 
        {
            if (i == 3) 
            {
                printf("No stove avaliable\n");
                usleep(300000);
                i = 0;
            }
        }
    }
}
