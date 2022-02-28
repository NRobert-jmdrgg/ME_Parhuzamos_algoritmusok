#include <stdio.h>
#include <stdlib.h>

#define ARR_LENGTH(x)  (sizeof(x) / sizeof((x)[0]))

void tomb_beolvas(int *arr, int len);
int tomb_sum(int *arr, int len);
int tomb_min(int *arr, int len);
int tomb_max(int *arr, int len);
int tomb_sum_rek(int *arr, int len, int i, int sum);
int tomb_min_rek(int *arr, int len, int i, int min);
int tomb_max_rek(int *arr, int len, int i, int max);

int main(int argc, char const *argv[])
{
    // const int LEN = 5;
    int arr[] = {1, 2, 2, 3, 2};

    // tomb_beolvas(arr, LEN);

    // for (int i = 0; i < LEN; i++)
    // {
    //     printf("%d ", arr[i]);
    // }
    
    // printf("%d ", tomb_sum(arr, ARR_LENGTH(arr)));

    // printf("%d ", tomb_max(arr, ARR_LENGTH(arr)));
    // printf("\n%d ", tomb_min(arr, ARR_LENGTH(arr)));
    // printf("\n%d", tomb_max_rek(arr, ARR_LENGTH(arr), ARR_LENGTH(arr) - 1, arr[0]));
    // printf("\n%d", tomb_min_rek(arr, ARR_LENGTH(arr), ARR_LENGTH(arr) - 1, arr[0]));

    
    return 0;
}

void tomb_beolvas(int *arr, int len)
{
    int ok;
    for (int i = 0; i < len; i++)
    {
        ok = 0;
        do
        {
            if (scanf("%d", &arr[i]) != 1)
            {
                printf("Rossz szam!\n");
                ok = 0;
            } 
            else
            {
                ok = 1;
            }
            while (getchar() != '\n') {}
        } while (!ok);   
    }
}

int tomb_sum(int *arr, int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += arr[i];
    }

    return sum;
}

int tomb_min(int *arr, int len)
{
    int min = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;   
}

int tomb_max(int *arr, int len)
{
    int max = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;      
}

int tomb_sum_rek(int *arr, int len, int i, int sum)
{
    if (i < 0)
    {
        return sum;
    }
    else
    {
        sum += arr[i];
        return tomb_sum_rek(arr, len, --i, sum);
    }   
}

int tomb_min_rek(int *arr, int len, int i, int min)
{
    if (i < 0)
    {
        return min;
    }
    
    if (arr[i] < min)
    {
        min = arr[i];
        return tomb_min_rek(arr, len, --i, min);
    }
    
    return tomb_min_rek(arr, len, --i, min);
}

int tomb_max_rek(int *arr, int len, int i, int max)
{
    if (i < 0)
    {
        return max;
    }
    
    if (arr[i] > max)
    {
        max = arr[i];
        return tomb_max_rek(arr, len, --i, max);
    }
    
    return tomb_max_rek(arr, len, --i, max);
}