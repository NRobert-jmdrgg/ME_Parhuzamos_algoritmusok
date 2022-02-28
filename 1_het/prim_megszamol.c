#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int is_prime(int num);
int primek_megszamol_idomeressel(int num);
void primek_szamai_kiir(int* intervallumok, int *primek_szamai);

/**
 * Definiáljon egy függvényt, amely az [1, n] intervallumon meghatározza a prímszámok számát! 
 * Mérje le a futási időt az n = 1000, 20000, 3000, ..., 20000 értékeknél, és jelenítse meg grafikonon a kapott eredményeket (például Excel-el)!
 */
int main()
{
    int intervallumok[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
                       11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000}; 
    
    int primek_szamai[20];

    for (int i = 0; i < 20; i++)
    {
        primek_szamai[i] = primek_megszamol_idomeressel(intervallumok[i]);
        printf("Az 1-tol %d-ig tarto intervallumon %d darab prim van \n", intervallumok[i], primek_szamai[i]);
    }
    
    primek_szamai_kiir(intervallumok, primek_szamai);
    return 0;
}

int is_prime(int num) 
{
    for (int i = 2; i <= num / 2; i++) 
    {
        if (num % i == 2) 
        {
            return 0;
        }
    }

    return 1;
}

int primek_megszamol_idomeressel(int num) 
{
    clock_t kezd = clock();

    int count = 0;
    for (int i = 1; i <= num; i++) 
    {
        count += is_prime(i);
    }

    clock_t vege = clock();

    double eltelt_ido = (double)(vege - kezd) / CLOCKS_PER_SEC;

    printf("\nEltelt masodpercek: %lf \n", eltelt_ido);

    return count;
}

void primek_szamai_kiir(int* intervallumok, int *primek_szamai) 
{
    FILE *f = fopen("primek.csv", "w");

    fprintf(f, "%s, %s, %s\n", "intervallum kezdete", "intervallum vege", "Primek szama");

    for (int i = 0; i < 20; i++)
    {
        fprintf(f, "%d, %d, %d\n", 1, intervallumok[i], primek_szamai[i]);
    }

    fclose(f);
    
}