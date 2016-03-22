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

int parse(char *str, char *argv[], const char* delim)
{
	int i = 0;
	argv[i] = strtok(str, delim);
	while(argv[i++] != NULL) {
		argv[i] = strtok(NULL, delim);
	}
	return i;
}

const char *dir_list[] = { "", "/bin/", "/sbin/" };

int run_cmd(char *argv[])
{
	int status;
	pid_t pid = fork();

	if(pid < 0) {
		fprintf(stderr, "*** Error: can't fork()\n");
		return pid;
	}
	else if(pid == 0) {
		char cmd[MAX_LEN];
		int i=0;
		while(i < 3) {
			sprintf(cmd, "%s%s", dir_list[i], argv[0]);
			execvp(cmd, argv);
			i++;
		}
		fprintf(stderr, "*** Error: Command '%s' uknown\n", argv[0]);
	}
	else {
		// write
		waitpid(-1, &pid, 0);
	}

	return status;
}

void cd(char *argv[])
{
	if(argv[1] != NULL) chdir(argv[1]);
}

int main()
{
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	const char *user = pw->pw_name;
	while(1) {
		char *cwd = getcwd(NULL, 0);
		printf("%s@ShellC:%s$ ", user, cwd);
		free(cwd);
		char str[MAX_LEN];
		char *pipes[MAX_ARGS];
		int i;
		fgets(str, MAX_LEN, stdin);
		parse(str, pipes, "|");
		for(i = 0; pipes[i] != NULL; i++) {
			//printf("%s\n", pipes[i]);
			char *argv[MAX_ARGS];
			parse(pipes[i], argv, " \t\n");
			if(argv[0] == NULL) continue;
			else if(!strcmp(argv[0], "exit")) exit(0);
			else if(!strcmp(argv[0], "cd")) cd(argv);
			else run_cmd(argv);
		}
	}

	return 0;
}
