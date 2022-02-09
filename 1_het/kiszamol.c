#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Írjon egy programot, amelyik 2 véletlenszerűen meghatározott pozitív egész szám értékét számoltatja ki a felhasználóval, 
 * és a szabványos bemeneten várja az eredményt! Ellenőrízze, hogy helyes az érték, és írja ki, hogy mennyi ideig tartott 
 * (másodpercben) a felhasználónak a számítás!
 */
int main()
{
    srand(time(NULL));

    int x, y, be;

    x = rand() % 10 + 1;
    y = rand() % 10 + 1;

    time_t start, veg;
    double eltelt;

    time(&start);

    printf("Szamold ki: %d + %d = ", x, y);
    scanf("%d", &be);

    while (be != x + y)
    {
        printf("\nRossz megoldas!\n");
        scanf("%d", &be);
    }

    printf("\nHelyes megoldas");
    
    time(&veg);

    eltelt = difftime(veg, start);

    printf("\nEltelt ido masodpercben: %lf", eltelt);

    return 0;
}
