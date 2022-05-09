#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define DIR_PATH "./test_dir2/"
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
    strcpy(new_filepath, DIR_PATH);
    strcat(new_filepath, file_extension);
    strcat(new_filepath, "/");
    struct stat st;
    // ./test_dir/ext/
    if (stat(new_filepath, &st) == -1) {
        mkdir(new_filepath, 0700);
    }
    strcat(new_filepath, filename);

    strcpy(old_filepath, DIR_PATH);
    strcat(old_filepath, filename);

    rename(old_filepath, new_filepath);
}

int main() {  //

    DIR *directory;
    if ((directory = opendir(DIR_PATH)) == NULL) {
        fprintf(stderr, "Nincs ilyen mappa: %s\n", DIR_PATH);
        exit(1);
    }

    clock_t begin = clock();
    struct dirent *entity;
    while ((entity = readdir(directory)) != NULL) {
        organize_by_extension(entity->d_name);
    }
    clock_t end = clock();
    printf("eltelt ido: %lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}
