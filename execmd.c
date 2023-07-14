#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "get_location.h"

void execmd(char **argv) {
    char *command = NULL;

    if (argv) {
        /* get the command */
        command = argv[0];

        if (strcmp(command, "ls") == 0) {
    /* check if "-la" option is provided */
    if (argv[1] && strcmp(argv[1], "-la") == 0) {
        /* execute ls -la command */
        argv[0] = "/bin/ls"; // or provide the path to ls executable
        argv[1] = "-la"; // set the second argument to -la
        if (execvp(argv[0], argv) == -1) {
            perror("Error:");
        }
    } else {
        /* execute ls command */
        if (execvp(argv[0], argv) == -1) {
            perror("Error:");
        }
    }
}

    }
}

