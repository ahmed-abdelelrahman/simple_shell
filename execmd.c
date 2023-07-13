#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void execmd(char **argv) {
    char *command = NULL;

    if (argv) {
        /* get the command */
        command = argv[0];

        /* check if the command is a directory */
        struct stat filestat;
        if (stat(command, &filestat) == 0) {
            if (S_ISDIR(filestat.st_mode)) {
                /* Command is a directory, so execute ls */
                DIR *dir = opendir(command);
                if (dir != NULL) {
                    struct dirent *entry;
                    while ((entry = readdir(dir)) != NULL) {
                        printf("%s\n", entry->d_name);
                    }
                    closedir(dir);
                } else {
                    perror("Error:");
                }
                return;
            }
        }

        /* execute the command with the shell */
        char cmd[100];
        snprintf(cmd, sizeof(cmd), "/bin/sh -c '%s'", command);
        system(cmd);
    }
}

