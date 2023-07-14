#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execmd(char **argv);

ssize_t getline(char **lineptr, size_t *n, FILE *stream)

char *strtok(char *str, const char *delim);

char *get_location(char *command);
