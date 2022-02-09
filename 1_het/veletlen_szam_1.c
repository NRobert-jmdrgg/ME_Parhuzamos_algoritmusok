#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * Generáljon véletlenszámot az [500 - 1000] intervallumon! (Oldja meg lebegőpontos és egész számok esetére is!)
 */
int main()
{
    srand(time(NULL));

    double range = 1000 - 500;
    double div = RAND_MAX / range;
    printf("random lebegos: %f\n", 500 + (rand() / div));
    
    printf("random egesz: %d", (rand() % (1000 - 500 + 1)) + 500);
    return 0;
}
