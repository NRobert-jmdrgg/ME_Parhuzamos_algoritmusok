#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void *routine();
void *routine2();

int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

void *routine()
{
    x++;
    sleep(3);
    printf("value of x = %d\n", x);
}

void *routine2()
{
    x++;
    sleep(3);
    printf("value of x = %d\n", x);
}