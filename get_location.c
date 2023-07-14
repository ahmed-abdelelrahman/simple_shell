#include "main.h"

char *get_location(char *command){
    char *path, *path_copy, *path_token, *file_path;
    int command_length, directory_length;
    struct stat buffer;

    path = getenv("PATH");

    if(path){

	    /* Duplicate the path string */
	    path_copy = strdup(path);

	    /* Get length of command */
	    command_length = strlen(command);

	    /* Break down the path_copy variable into individual tokens */
	    path_token = strtok(path_copy, ":");

	    while(path_token != NULL){
		    
		    /* Get length of directory */
		    directory_length = strlen(path_token);

		    /* Allocate memory for storing command name */
		    file_path = malloc(command_length + directory_length + 2);
		    
		    /* To build the path for the command */
		    strcpy(file_path, path_token);
		    strcat(file_path, "/");
		    strcat(file_path, command);
		    strcat(file_path, "\0");

		    /* Check if file path exits & return it, otherwise try another directory */
		    if (stat(file_path, &buffer) == 0){

			    /* free up allocated memory */
			    free(path_copy);

			    return (file_path);
		    }
		    else{
			    /* free up the file_path memory */
			    free(file_path);
			    path_token = strtok(NULL, ":");
		    }

	    }

	    free(path_copy);

	    if (stat(command, &buffer) == 0)
        {
            return (command);
        }


        return (NULL);

    }
    
    return (NULL);

}
