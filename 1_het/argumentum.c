#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * Készítsen egy programot, amely a bemeneti argumentumként kapott két egész szám között (zárt intervallumon) generál egy szintén egész véletlen számot! 
 * Ellenőrízze az argumentumok számát, és jelezzen hibát, amennyiben nem megfelelőek!
 */
int main()
{
    srand(time(NULL));

    int also, felso;
    printf("Also hatar: ");
    scanf("%d", &also);
    printf("\nFelso hatar: ");
    scanf("%d", &felso);

    printf("\nrandom: %d", (rand() % (felso - also + 1)) + also);
    return 0;
}
