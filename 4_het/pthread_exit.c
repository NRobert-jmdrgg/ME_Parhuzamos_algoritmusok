#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


void *roll_dice();

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    pthread_t th;
    int *res;
    pthread_create(&th, NULL, &roll_dice, NULL);

    pthread_exit(0);

    pthread_join(th, (void **) &res);

    printf("\ngot %d", *res);
    free(res);
    return 0;
}

void *roll_dice() 
{
    int val = rand() % 6 + 1;
    int *res = malloc(sizeof(int));
    *res = val;
    printf("thread result : %d\n", val);
    pthread_exit((void *)res);
}