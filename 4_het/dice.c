#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

int diceValues[8];
int status[8] = { 0 };

void *rollDice(void *arg);

int main(int argc, char const *argv[])
{
     
    return 0;
}

void *rollDice(void *arg)
{

}