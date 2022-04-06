#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define LENGTH(arr) ((sizeof(arr)) / sizeof(arr[0]))
#define DEFAULT_SIZE 10

typedef struct text_t {
    char **arr;
    int len;
    int size;
} text_t;

text_t getParagraphs(const char *filename) {
    text_t text = {
        .arr = malloc(DEFAULT_SIZE * sizeof(char *)),
        .len = 0,
        .size = DEFAULT_SIZE
    };
    
    FILE *fp = fopen(filename, "rt");
    if (!fp) { perror("Nem sikerult megnyitni\n"); exit(3); }

    char *line = NULL;
    size_t l = 0;
    ssize_t nread;

    while ((nread = getline(&line, &l, fp)) != -1) {
        if (text.len == text.size) {
            text.arr = realloc(text.arr, text.size * sizeof(char *) * 2);
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

int countWord(text_t text, const char *word) {
    int count = 0;
    
    int increment = strlen(word);
    for (int i = 0; i < text.len; i++) {
        for (char* s = text.arr[i]; (s = strstr(s, word)); s += increment) {
            ++count;
        }
        // printf("%d ediksorban %s %d szer szerepel\n", i, word, debug_count);
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    switch (argc) {
        case 1: perror("Nem adtal meg file-t\n"); exit(1);
        case 2: perror("Nem adtal meg kifejezest\n"); exit(2);
    }

    const char *filename = argv[1];
    const char *word = argv[2];

    text_t t = getParagraphs(filename);
    
    int count = countWord(t, word);
    printf("\ncount: %d\n", count);

    for (int i = 0; i < t.len; i++) 
        free(t.arr[i]);
    
    free(t.arr);
    return 0;
}
