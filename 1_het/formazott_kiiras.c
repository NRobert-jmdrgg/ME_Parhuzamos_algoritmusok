#include <stdio.h>
#include <stdlib.h>

/**
 * Írjon egy programot, amelyik egész értékeket ír ki pontosan 8 karakter hosszan (jobbra igazítva)! 
 * Oldja meg úgy, hogy szóközökkel, továbbá hogy 0 értékekkel van kitöltve a szám eleje (amennyiben szükséges kitölteni)!
 */
int main()
{
    int szam = 88888;
    printf("%8d", szam);

    int nullaval_kezdodo_szam = 0777;
    printf("\n%8o", nullaval_kezdodo_szam);
    return 0;
}
