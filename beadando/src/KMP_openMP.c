#include <ctype.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGTH(arr) ((sizeof(arr)) / sizeof(arr[0]))
#define DEFAULT_SIZE 10
#define THREAD_COUNT 32

typedef struct text {
    char** arr;
    int len;
    int size;
} text;

text t;

void fill_LPS(const char* pattern, int m, int* lps) {
    int len = 0;

    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch_Count(const char* pattern, const char* line) {
    int count = 0;
    int m = strlen(pattern);
    int n = strlen(line);
    int lps[m];

    fill_LPS(pattern, m, lps);

    int i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == line[i]) {
            j++;
            i++;
        }

        if (j == m) {
            count++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != line[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return count;
}

text getLines(const char* filename) {
    text text = {.arr = malloc(DEFAULT_SIZE * sizeof(char*)), .len = 0, .size = DEFAULT_SIZE};

    FILE* fp = fopen(filename, "rt");
    if (!fp) {
        perror("Nem sikerult megnyitni\n");
        exit(3);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, fp)) != -1) {
        if (text.len == text.size) {
            text.arr = realloc(text.arr, text.size * sizeof(char*) * 2);
            text.size *= 2;
        }
        text.arr[text.len] = malloc(nread * sizeof(char) + 1);
        strcpy(text.arr[text.len], line);
        text.len++;
    }
    free(line);
    fclose(fp);

    return text;
}

int count_words(const char* word) {
    int count = 0;
#pragma omp parallel for reduction(+ : count)
    for (int i = 0; i < t.len; i++) {
        count += KMPSearch_Count(word, t.arr[i]);
    }
    return count;
}

int main(int argc, char* argv[]) {
    switch (argc) {
        case 1:
            perror("Nem adtal meg file-t\n");
            exit(1);
        case 2:
            perror("Nem adtal meg kifejezest\n");
            exit(2);
    }

    const char* filename = argv[1];
    const char* word = argv[2];

    t = getLines(filename);

    double start = omp_get_wtime();

    int count = count_words(word);

    double end = omp_get_wtime();

    printf("Count: %d\n", count);

    printf("Work took %f seconds\n", end - start);

    return 0;
}