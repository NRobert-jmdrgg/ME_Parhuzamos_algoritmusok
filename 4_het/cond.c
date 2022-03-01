#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mut_fuel;
pthread_cond_t cond_fuel;

int fuel = 0;

void *fuel_filling(void *arg);
void *car(void *arg);

int main(int argc, char const *argv[])
{
    pthread_t th[2];
    pthread_mutex_init(&mut_fuel, NULL);
    pthread_cond_init(&cond_fuel, NULL);
    
    pthread_create(&th[0], NULL, &fuel_filling, NULL);
    pthread_create(&th[1], NULL, &car, NULL);
    
    for (size_t i = 0; i < 2; i++)
    {
        pthread_join(th[i], NULL);
    }
    

    pthread_mutex_destroy(&mut_fuel);
    pthread_cond_destroy(&cond_fuel);
    return 0;
}

void *fuel_filling(void *arg)
{
    for (size_t i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mut_fuel);
        fuel += 15;
        printf("filled fuel.. %d\n", fuel);
        pthread_mutex_unlock(&mut_fuel);
        pthread_cond_signal(&cond_fuel);
        sleep(1);
    }
    
}

void *car(void *arg)
{
    pthread_mutex_lock(&mut_fuel);
    while (fuel < 40) 
    {
        printf("No fuel.. waiting\n");
        pthread_cond_wait(&cond_fuel, &mut_fuel);
    }
    
    fuel -= 40;

    printf("Got fuel... left: %d\n", fuel);
    pthread_mutex_unlock(&mut_fuel);
}