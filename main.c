#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "execmd.h"

#define MAX_INPUT_LENGTH 100

int main(void) {
  char *prompt = "(Eshell) $ ";
  char *full_command = NULL;
  size_t n = 0;
  ssize_t nchars_read;
  char *token;
  const char *delim = " \n";
  char **argv;
  int i = 0;
  int num_tokens = 0;

  while (1) {
    printf("%s", prompt);
    fflush(stdout);

    nchars_read = getline(&full_command, &n, stdin);

    if (nchars_read == -1) {
      printf("Exiting shell....\n");
      break;
    } else {
      token = strtok(full_command, delim);

      while (token != NULL) {
        num_tokens++;
        token = strtok(NULL, delim);
      }
      num_tokens++;

      argv = malloc(sizeof(char *) * num_tokens);

      token = strtok(full_command, delim);

      for (i = 0; token != NULL; i++) {
        argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(argv[i], token);
        token = strtok(NULL, delim);
      }

      // Remove newline character from the last token if present
      if (i > 0 && argv[i - 1][strlen(argv[i - 1]) - 1] == '\n') {
        argv[i - 1][strlen(argv[i - 1]) - 1] = '\0';
      }

      argv[i] = NULL;

      execmd(argv);

      for (i = 0; argv[i] != NULL; i++) {
        free(argv[i]);
      }
      free(argv);
    }
  }

  free(full_command);

  return 0;
}

