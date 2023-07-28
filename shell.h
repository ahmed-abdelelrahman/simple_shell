#ifndef _SHELL_H_
#define _SHELL_H_

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

#define HIST_FILE	".simple_shell_history"
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


/* my_loops.c */
int loop_mina(info_t *, char **);
int find_built_command(info_t *);
void find_command(info_t *);
void fork_command_thread(info_t *);

/* my_execute.c */
int execue_file(info_t *, char *);
char *duplo_chars(char *, int, int);
char *see_full_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* my_error.c */
void insert_string(char *);
int insert_char(char);
int write_char(char c, int fd);
int print_string(char *str, int fd);

/* my_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* my_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* my_info.c */
char *copy_string(char *, char *, int);
char *conc_string(char *, char *, int);
char *locate_string(char *, char);

/* my_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* my_fill_memory.c */
char *_memset_memory(char *, char, unsigned int);
void ffree_string(char **);
void *_reallocs_block(void *, unsigned int, unsigned int);

/* my_memory.c */
int free_me(void **);

/* my_atoi.c */
int interactive(info_t *);
int delim(char, char *);
int alpha(int);
int _atoi(char *);

/* my_error1.c */
int strconvint(char *);
void write_err(info_t *, char *);
int write_dec(int, int);
char *convert_num(long int, int, int);
void remove_comment(char *);

/* my_built.c */
int mina_robir_myexit(info *);
int robir_mycd(info *);
int robir_myhelp(info_t *);

/* my_built1.c */
int show_history(info_t *);
int mimics_alias(info_t *);

/*my_line.c */
ssize_t input_buffers(info_t *);
int get_next_line(info_t *, char **, size_t *);
void block_ctrl_C(int);

/* my_info.c */
void remove_info(info_t *);
void init_info(info_t *, char **);
void free_info_t(info_t *, int);

/* my_viron.c */
char *get_evironment(info_t *, const char *);
int my_environment(info_t *);
int set_environment(info_t *);
int unset_environment(info_t *);
int populate_environment_list(info_t *);

/* my_viron1.c */
char **get_environment(info_t *);
int unset_environment(info_t *, char *);
int set_environment(info_t *, char *, char *);

/* my_file_history.c */
char *get_file(info_t *info);
int add_file(info_t *info);
int read_file(info_t *info);
int add_list(info_t *info, char *buf, int linecount);
int rnum_history(info_t *info);

/* my_list.c */
list_t *add_node_from_start(list_t **, const char *, int);
list_t *add_node_to_end(list_t **, const char *, int);
size_t print_list_string(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list_nodes_mina(list_t **);

/* my_list1.c */
size_t list_len_mina(const list_t *);
char **arr_to_string(list_t *);
size_t print_all_list_t(const list_t *);
list_t *node_starts_with_prefix(list_t *, char *, char);
ssize_t get_node_at_index(list_t *, list_t *);

/* my_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
