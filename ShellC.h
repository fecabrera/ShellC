#ifndef __SHELL_C
#define __SHELL_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pwd.h>

#define MAX_ARGS 256
#define MAX_LEN 1024

#define PARENT_READ 1
#define PARENT_WRITE 0

#define CHILD_READ 0
#define CHILD_WRITE 1

#define READ 0
#define WRITE 1

extern const char *dir_list[];

void ShellError(const char *str);
void CommandNotFound(const char *cmd);
int parse(char *str, char *argv[], const char* delim);
int get_dir(const char *home, const char *path, char *str);
int run_cmd(char *argv[], int index, int npipes, int *in_pipe, int *out_pipe);
void cd(char *argv[]);

#endif // __SHELL_C