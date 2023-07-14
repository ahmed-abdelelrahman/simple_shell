#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *get_location(char *command) {
    char *path = getenv("PATH");
    char *path_copy = NULL;
    char *path_token = NULL;
    char *file_path = NULL;
    int command_length = strlen(command);
    int directory_length = 0;
    struct stat buffer;

    if (!path)
        return NULL;

    path_copy = strdup(path);
    path_token = strtok(path_copy, ":");

    while (path_token != NULL) {
        directory_length = strlen(path_token);
        file_path = malloc(directory_length + command_length + 2);
        strcpy(file_path, path_token);
        strcat(file_path, "/");
        strcat(file_path, command);

        if (stat(file_path, &buffer) == 0) {
            free(path_copy);
            return file_path;
        }

        free(file_path);
        path_token = strtok(NULL, ":");
    }

    free(path_copy);

    if (stat(command, &buffer) == 0) {
        return command;
    }

    return NULL;
}

