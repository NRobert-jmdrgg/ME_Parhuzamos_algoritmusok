#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double start;

void print_matrix(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
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

bool find_unassigned(int sudoku[9][9], int *row, int *col) {
    for (*row = 0; *row < 9; (*row)++) {
        for (*col = 0; *col < 9; (*col)++) {
            if (sudoku[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

int solve(int sudoku[9][9], int level) {
    int row = 0;
    int col = 0;

    if (!find_unassigned(sudoku, &row, &col)) return 1;

    for (int num = 1; num <= 9; num++) {
        if (is_safe(sudoku, row, col, num)) {
#pragma omp task default(none) firstprivate(sudoku, row, col, num, level) shared(start)
            {
                int copy[9][9];
                memcpy(copy, sudoku, 9 * 9 * sizeof(int));
                copy[row][col] = num;
                if (solve(copy, level + 1)) {
                    print_matrix(copy);
                    double end = omp_get_wtime();
                    double time_spent = end - start;
                    printf("\eltelt ido: %lf s\n", time_spent);
                    exit(0);
                }
            }
        }
    }

#pragma omp taskwait
    return 0;
}

int main() {
    omp_set_nested(true);
    int **sudoku;

    int easy_s[9][9] = {
        {9, 0, 2, 4, 1, 5, 0, 0, 0}, {0, 0, 5, 0, 6, 0, 0, 0, 0}, {3, 7, 0, 0, 0, 0, 0, 6, 1},
        {2, 1, 0, 3, 9, 6, 0, 0, 5}, {4, 0, 6, 0, 0, 0, 0, 0, 2}, {0, 0, 3, 0, 8, 0, 1, 9, 0},
        {6, 4, 9, 0, 3, 1, 0, 5, 7}, {5, 0, 0, 6, 0, 0, 0, 0, 4}, {8, 0, 7, 5, 0, 9, 0, 0, 0}};

    int medium_s[9][9] = {
        {0, 6, 0, 0, 7, 0, 4, 1, 0}, {0, 0, 0, 0, 2, 9, 7, 0, 0}, {0, 7, 4, 0, 6, 0, 9, 0, 8},
        {0, 0, 0, 0, 0, 0, 2, 0, 4}, {0, 0, 0, 0, 0, 2, 0, 5, 0}, {0, 1, 8, 7, 0, 0, 0, 0, 0},
        {5, 3, 1, 9, 0, 0, 0, 0, 2}, {0, 0, 0, 0, 0, 0, 5, 0, 0}, {0, 4, 0, 0, 5, 7, 0, 3, 1}};

    int hard_s[9][9] = {
        {0, 6, 5, 0, 0, 0, 0, 1, 9}, {0, 0, 3, 0, 0, 0, 0, 0, 6}, {0, 0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 0}, {1, 0, 0, 0, 3, 0, 0, 0, 7}, {0, 7, 0, 5, 2, 6, 0, 0, 0},
        {0, 8, 0, 0, 0, 0, 9, 7, 0}, {0, 3, 0, 0, 5, 0, 2, 0, 0}, {9, 1, 0, 6, 0, 4, 0, 0, 0}};

    int expert_s[9][9] = {
        {0, 0, 0, 0, 0, 0, 8, 0, 0}, {2, 1, 0, 3, 0, 0, 0, 0, 0}, {7, 0, 3, 2, 4, 0, 0, 0, 0},
        {0, 6, 0, 4, 5, 0, 0, 0, 8}, {0, 8, 5, 0, 0, 6, 0, 0, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0, 4}, {6, 0, 0, 0, 0, 3, 0, 5, 0}, {0, 0, 0, 0, 0, 0, 6, 1, 0}};

    int evil_s[9][9] = {
        {3, 0, 0, 0, 0, 0, 0, 0, 5}, {0, 2, 5, 0, 0, 8, 0, 1, 0}, {6, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 4, 0, 0}, {2, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 7, 9, 0, 8, 0, 0, 0, 6},
        {0, 0, 0, 9, 0, 0, 0, 6, 0}, {0, 0, 3, 0, 0, 0, 0, 0, 0}, {0, 5, 8, 0, 7, 0, 0, 0, 9}};

    sudoku = easy_s;

    start = omp_get_wtime();
#pragma omp parallel default(none) shared(sudoku) num_threads(4)
#pragma omp master
    solve(sudoku, 1);

    return 0;
}
