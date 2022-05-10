#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define LENGTH(arr) ((sizeof(arr)) / sizeof(arr[0]))
#define DEFAULT_SIZE 10
#define THREAD_COUNT 32

typedef struct text {
    char **arr;
    int len;
    int size;
} text;

text t;

text getParagraphs(const char *filename) {
    text text = {.arr = malloc(DEFAULT_SIZE * sizeof(char *)), .len = 0, .size = DEFAULT_SIZE};

    FILE *fp = fopen(filename, "rt");
    if (!fp) {
        perror("Nem sikerult megnyitni\n");
        exit(3);
    }

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

typedef struct args {
    const char *word;
    int *start;
    int end;
    // int *thread_num;
} args;

void *countWord(void *arg) {
    args *a = (args *)arg;

    int *count = malloc(sizeof(int));
    *count = 0;
    int increment = strlen(a->word);
    for (int i = *(a->start); i < a->end && i < t.len; i++) {
        for (char *s = t.arr[i]; (s = strstr(s, a->word)); s += increment) {
            printf("%s\n", s);
            sleep(10);
            (*count)++;
        }
    }

    free(a->start);
    free(a);

    return (void *)count;
}

int main(int argc, char *argv[]) {
    switch (argc) {
        case 1:
            perror("Nem adtal meg file-t\n");
            exit(1);
        case 2:
            perror("Nem adtal meg kifejezest\n");
            exit(2);
    }

    const char *filename = argv[1];
    const char *word = argv[2];

    t = getParagraphs(filename);

    pthread_t threads[THREAD_COUNT];

    const int step =
        (t.len % THREAD_COUNT == 0) ? (t.len / THREAD_COUNT) : (t.len / THREAD_COUNT) + 1;

    struct timeval t0, t1, dt;
    gettimeofday(&t0, NULL);

    int i;
    for (i = 0; i < THREAD_COUNT; i++) {
        args *arg = malloc(sizeof(args));
        int *a = malloc(sizeof(int));
        *a = i * step;
        (*arg).start = a;
        (*arg).word = word;
        (*arg).end = *(arg->start) + step;
        pthread_create(&threads[i], NULL, countWord, (void *)arg);
    }

    int globalCount = 0;
    int *returned_value = malloc(sizeof(int));
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], (void **)&returned_value);
        globalCount += *returned_value;
    }
    free(returned_value);

    printf("Count: %d\n", globalCount);

    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &dt);
    printf("%ld.%06ld sec\n", dt.tv_sec, dt.tv_usec);

    for (i = 0; i < t.len; i++) free(t.arr[i]);

    free(t.arr);
    return 0;
}
