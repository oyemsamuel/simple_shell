#ifndef _SAM_ALI_SHELL_H_
#define _SAM_ALI_SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>


#define CMD_NORM	0
#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_OR		1

#define MAX_ALLOWED_FD 100

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024

#define USE_STRTOK 0
#define USE_GETLINE 0

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

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
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* sam_ali_shloop.c */
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);

/* loophsh.c */
int loophsh(char **);

/* sam_ali_errors.c */
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);

/* sam_ali_string.c */
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);

/* sam_ali_string1.c */
char *_strdup(const char *);
void _puts(char *);
char *_strcpy(char *, char *);
int _putchar(char);

/* sam_ali_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* sam_ali_realloc.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* sam_ali_memory.c */
int bfree(void **);

/* sam_ali_atoi.c */
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);

/* sam_ali_errors1.c */
void print_error(info_t *, char *);
int _erratoi(char *);
int print_d(int, int);
void remove_comments(char *);
char *convert_number(long int, int, int);

/* sam_ali_builtin.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

/* sam_ali_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* sam_ali_parser.c */
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);

/* sam_ali_getline.c */
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t get_input(info_t *);

/* sam_ali_getinfo.c */
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);

/* sam_ali_environ.c */
char *_getenv(info_t *, const char *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _myenv(info_t *);

/* sam_ali_getenv.c */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/* sam_ali_vars.c */
int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);
int replace_alias(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);

/* sam_ali_history.c */
int write_history(info_t *info);
int read_history(info_t *info);
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* sam_ali_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* sam_ali_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* sam_ali_exits.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);


#endif /* _SAM_ALI_SHELL_H_ */