#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execmd(char **argv) {
    char *command = NULL;

    if (argv) {
        /* get the command */
        command = argv[0];

        /* handle specific commands */
        if (strcmp(command, "ls") == 0) {
            /* check if "-la" option is provided */
            if (argv[1] && strcmp(argv[1], "-la") == 0) {
                /* execute ls -la command */
                argv[0] = "/bin/ls"; // or provide the path to ls executable
                if (execvp(argv[0], argv) == -1) {
                    perror("Error:");
                }
            } else {
                /* execute ls command */
                if (execvp(argv[0], argv) == -1) {
                    perror("Error:");
                }
            }
        } else {
            /* execute other commands with execvp */
            if (execvp(command, argv) == -1) {
                perror("Error:");
            }
        }
    }
}

