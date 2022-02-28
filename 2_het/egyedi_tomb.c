#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_LENGTH(x)  (sizeof(x) / sizeof((x)[0]))

void tomb_random_feltolt_egyedi(int *arr, int len, int min, int max);
int linear_search(int *arr, int from, int num);

int main()
{
    srand(time(NULL));
    const int len = 10;
    int arr[len];

    tomb_random_feltolt_egyedi(arr, len, 0, 11);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    
    return 0;
}

