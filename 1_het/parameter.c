#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double tomb_kiir_es_idomer(int *tomb, int size);
void idok_kiir(char* filenev, double random_ido, double kiirasi_ido);
/**
 * Készítsen egy programot, amelyik a paraméterként vár egy fájlnevet és egy elemszámot (mint egész értéket).
 * Ezek alapján hozza létre a program az adott fájlt véletlenszerű értékekkel kitöltve, a megfelelő elemszámmal!
 * Mérje le a véletlenszámok generálásának sebességét az elemszám függvényében!
 * Mérje le a fájl mentésének idejét az elemszám függvényében!
 * Gyűjtse össze a kapott mérési adatokat táblázatba, és ábrázolja őket grafikonon!
 */
int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc < 2) 
    {
        printf("Nincs eleg parameter\n");
        exit(-1);
    } else 
    {
        clock_t start, end;
        
        char *filenev = argv[0];
        int size = atoi(argv[1]);
        int tomb[size]; 

        start = clock();

        for (int i = 0; i < size; i++)
        {
            tomb[i] = rand() % 10 + 1;
        }
        
        end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC;

        double write_time = tomb_kiir_es_idomer(tomb, size);

        idok_kiir(filenev, time, write_time);
    }
    
    
    return 0;
}

double tomb_kiir_es_idomer(int *tomb, int size) 
{
    clock_t start, end;

    FILE *f = fopen("szamok.txt", "w");

    start = clock();

    for (int i = 0; i < size; i++)
    {
        fprintf(f, "%d ", tomb[i]);
    }

    end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;

    fclose(f);

    return time;
}

void idok_kiir(char* filenev, double random_ido, double kiirasi_ido) 
{
    FILE *f = fopen(filenev, "w");

    fprintf(f, "Veletlen szam generalas, kiirasi ido");

    fprintf(f, "%ld, %ld", random_ido, kiirasi_ido);

    fclose(f);
}