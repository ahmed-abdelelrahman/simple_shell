#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".my_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* my_shell_loop.c */
int my_shell(info_t *, char **);
int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* my_parser.c */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* main.c */
int main(int ac, char **av);
void custom_init(info_t *info);
void my_shell_function(info_t *info, char **av);
void custom_cleanup(info_t *info);
/* my_errors.c */
void print_error_message(char *);
int print_char_to_fd(char, int);
int print_string_to_fd(char *, int);
void print_string(char *);
int print_char(char);

/* my_string.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* my_string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int print_character(char);

/* my_exits.c */
char *string_copy_n(char *, char *, int);
char *string_concat_n(char *, char *, int);
char *find_character(char *, char);

/* my_tokenizer.c */
char **tokenize_string(char *, char *);
char **tokenize_string2(char *, char);

/* my_realloc.c */
char *memory_set(char *, char, unsigned int);
void free_memory(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* my_memory.c */
int free_block(void **);

/* my_atoi.c */
int is_interactive(info_t *);
int is_delimiter(char, char *)
int is_alpha(int);
int my_atoi(char *);

/* my_errors1.c */
int error_atoi(char *);
void print_error(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* my_builtin.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/* my_builtin1.c */
int my_history(info_t *);
int my_alias(info_t *);

/* my_getline.c */
ssize_t get_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigint_handler(int);
ssize_t custom_input_buf(info_t *info, char **buf, size_t *len);
ssize_t custom_get_input(info_t *info);
ssize_t custom_read_buf(info_t *info, char *buf, size_t *i);
int custom_getline(info_t *info, char **ptr, size_t *length);
void custom_sigintHandler(__attribute__((unused))int sig_num);
int custom_puts(const char *str);
char *custom_strchr(const char *s, int c);
char *custom_strncpy(char *dest, const char *src, size_t n);
char *custom_strncat(char *dest, const char *src, size_t n);
void *custom_realloc(void *ptr, size_t old_size, size_t new_size);
void custom_free(void *ptr);
size_t custom_strlen(const char *s);
void check_chain(info_t *info, char *buf, size_t *j, size_t i, size_t len);
int is_chain(info_t *info, char *buf, size_t *j);


/* my_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* my_environ.c */
char *get_environment(info_t *, const char *);
int my_environment(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int populate_environment_list(info_t *);

/* my_getenv.c */
char **get_environment_variables(info_t *);
int unset_environment_variable(info_t *, char *);
int set_environment_variable(info_t *, char *, char *);

/* my_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* my_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_string(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* my_lists1.c */
size_t list_length(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* my_vars.c */
int is_command_chain(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);

#endif
