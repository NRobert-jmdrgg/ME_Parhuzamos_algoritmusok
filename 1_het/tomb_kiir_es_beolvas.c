#include <stdio.h>
#include <stdlib.h>

void int_tomb_kiir(int *tomb);
void long_tomb_kiir(long *tomb);
void float_tomb_kiir(float *tomb);
int file_meret(char *filenev);
void kiolvas(char *filenev);
/**
 * Írjon egy programot, amely egy tömbben lévő értékeket kiírja egy fájlba!
 * A műveletet szervezze ki egy külön függvénybe! 
 * Készítse el int, long és float típusok esetére is (külön függvényekkel)!
 * Kérdezze le, hogy az adott útvonalon lévő fájlnak mekkora a mérete!
 * Készítse el a függvényeket az adatok visszaolvasásához!
 */
int main()
{
    int egesz_tomb[] = {1, 4, 7, 9};
    long hosszu_tomb[] = {585371481, 374819842, 3917151, 74124124};
    float lebego_tomb[] = {1.63, 4.2141, 7.241, 9.2141};

    int_tomb_kiir(egesz_tomb);
    long_tomb_kiir(hosszu_tomb);
    float_tomb_kiir(lebego_tomb);

    printf("\nLong filemeret: %d\n", file_meret("long.txt"));

    kiolvas("long.txt");
    return 0;
}

void int_tomb_kiir(int *tomb) 
{
    FILE *f = fopen("int.txt", "w");

    for (int i = 0; i < 4; i++) 
    {
        fprintf(f, "%d ", tomb[i]);
    }

    fclose(f);
}

void long_tomb_kiir(long *tomb) 
{
    FILE *f = fopen("long.txt", "w");

    for (int i = 0; i < 4; i++) 
    {
        fprintf(f, "%ld ", tomb[i]);
    }

    fclose(f);
}

void float_tomb_kiir(float *tomb) 
{
    FILE *f = fopen("float.txt", "w");

    for (int i = 0; i < 4; i++) 
    {
        fprintf(f, "%f ", tomb[i]);
    }

    fclose(f);
}

int file_meret(char *filenev) 
{
    FILE *f = fopen(filenev, "r");

    fseek(f, 0L, SEEK_END);

    int meret = ftell(f);

    fclose(f);

    return meret;
}

void kiolvas(char *filenev) 
{
    FILE *f = fopen(filenev, "r");
    
    char c = fgetc(f);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(f);
    }

    fclose(f);
}