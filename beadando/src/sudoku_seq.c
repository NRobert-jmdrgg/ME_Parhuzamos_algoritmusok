#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 9

void print_sudoku(int sudoku[LEN][LEN]) {
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            printf("%d ", sudoku[i][j]);
            if (j == 2 || j == 5) printf(" ");
        }
        if (i == 2 || i == 5) printf("\n");

        printf("\n");
    }
    printf("\n");
}

bool is_safe(int sudoku[9][9], int row, int col, int num) {
    int row0 = (row / 3) * 3;
    int col0 = (col / 3) * 3;
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == num) {
            return false;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][col] == num) {
            return false;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[row0 + i][col0 + j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool fill_cells(int sudoku[LEN][LEN], int row, int col) {
    if (row == LEN - 1 && col == LEN) return true;

    if (col == LEN) {
        row++;
        col = 0;
    }

    if (sudoku[row][col]) return fill_cells(sudoku, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (is_safe(sudoku, row, col, num)) {
            sudoku[row][col] = num;
            if (fill_cells(sudoku, row, col + 1)) return true;
        }
        sudoku[row][col] = 0;
    }
    return false;
}

int main(int argc, char const *argv[]) {
    int sudoku[9][9] = {{5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
                        {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
                        {4, 0, 0, 8, 0, 3, 0, 0, 1}, {0, 6, 0, 0, 0, 0, 2, 8, 0},
                        {0, 0, 0, 4, 1, 9, 0, 0, 5}, {0, 0, 0, 0, 8, 0, 0, 7, 9}};
    printf("kitoltve: \n");

    double start = clock();
    if (fill_cells(sudoku, 0, 0)) print_sudoku(sudoku);

    double end = clock();

    printf("Eltelt ido: %lf", (end - start) / CLOCKS_PER_SEC);

    return 0;
}
