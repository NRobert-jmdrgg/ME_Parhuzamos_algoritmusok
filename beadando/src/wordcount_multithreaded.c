#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <math.h>

#define LENGTH(arr) ((sizeof(arr)) / sizeof(arr[0]))
#define DEFAULT_SIZE 10
#define THREAD_COUNT 32

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
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, fp)) != -1) {
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

typedef struct arg_t {
    text_t text;
    const char *word;
    int *start;
    int end;
    // int *thread_num;
} arg_t;

void *countWord(void *arg) {
    arg_t *a = (arg_t *)arg;

    // printf("Hello from thread %d\n", *(a->thread_num));
    int *count = malloc(sizeof(int));
    *count = 0;
    int increment = strlen(a->word);
    for (int i = *(a->start); i < a->end && i < a->text.len; i++) {
        for (char* s = a->text.arr[i]; (s = strstr(s, a->word)); s += increment) {
            (*count)++;
        }
    }

    // printf("thread %d start %d end %d count %d\n", *(a->thread_num), *(a->start), a->end, *count);
    
    // free(a->thread_num);
    free(a->start);
    free(a);
    return (void *) count;
}

int main(int argc, char *argv[]) {
    switch (argc) {
        case 1: perror("Nem adtal meg file-t\n"); exit(1);
        case 2: perror("Nem adtal meg kifejezest\n"); exit(2);
    }

    const char *filename = argv[1];
    const char *word = argv[2];

    text_t t = getParagraphs(filename);

    printf("\n size: %d\n", t.len);

    pthread_t threads[THREAD_COUNT];
    
    const int step = ( t.len % THREAD_COUNT == 0 ) ? (t.len / THREAD_COUNT) : (t.len / THREAD_COUNT) + 1;

    int i;
    for (i = 0; i < THREAD_COUNT; i++) {
        arg_t *arg = malloc(sizeof(arg_t));
        int *a = malloc(sizeof(int));
        // int *tn = malloc(sizeof(int));
        *a = i * step;
        // *tn = i;
        // (*arg).thread_num = tn;
        (*arg).start = a;
        (*arg).text = t;
        (*arg).word = word;
        (*arg).end = *(arg->start) + step;
        pthread_create(&threads[i], NULL, countWord, (void *) arg);
    }
    
    int globalCount = 0;
    int *returned_value = malloc(sizeof(int));
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], (void **) &returned_value);
        globalCount += *returned_value;
    }
    free(returned_value);

    printf("Count: %d\n", globalCount);

    for (i = 0; i < t.len; i++) 
        free(t.arr[i]);
    
    free(t.arr);
    return 0;
}
