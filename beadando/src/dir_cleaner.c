#include <dirent.h>
#include <errno.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define DIR_PATH "./test_dir/"
#define MAX_PATHLEN 4096

const char *get_fileextension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return "";
    return dot + 1;
}

// ./test_dir/file.ext -> ./test_dir/ext/file.ext
void organize_by_extension(const char *filename) {
    const char *file_extension = get_fileextension(filename);
    char new_filepath[MAX_PATHLEN];
    char old_filepath[MAX_PATHLEN];
#pragma omp parallel sections firstprivate(file_extension) lastprivate(new_filepath, old_filepath) \
    shared(filename) num_threads(2)
    {
#pragma omp section
        {
            strcpy(new_filepath, DIR_PATH);
            strcat(new_filepath, file_extension);
            strcat(new_filepath, "/");
            struct stat st;
            // ./test_dir/ext/
            if (stat(new_filepath, &st) == -1) {
                mkdir(new_filepath, 0700);
            }
            strcat(new_filepath, filename);
        }

#pragma omp section
        {
            strcpy(old_filepath, DIR_PATH);
            strcat(old_filepath, filename);
        }
    }

    rename(old_filepath, new_filepath);
}

int main() {  //
    omp_set_nested(true);

    DIR *directory;
    if ((directory = opendir(DIR_PATH)) == NULL) {
        fprintf(stderr, "Nincs ilyen mappa: %s\n", DIR_PATH);
        exit(1);
    }

    struct dirent *entity;
    double start = omp_get_wtime();
#pragma omp parallel private(entity) shared(directory)
    while ((entity = readdir(directory)) != NULL) {
        organize_by_extension(entity->d_name);
    }
    double end = omp_get_wtime();

    printf("ido: %lf\n", end - start);
    return 0;
}
