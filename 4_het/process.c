#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int x = 2;
    int pid = fork();
    
    if (pid == -1) 
    {
        return 1;
    }

    printf("Hello from precesses %d \n", getpid());

    if (pid == 0)
    {
        x++;
    }
    sleep(2);    
    printf("\n%d\n", x);


    if (pid != 0)
    {
        wait(NULL);
    }
    return 0;
}

