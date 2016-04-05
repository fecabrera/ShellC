#include "ShellC.h"

void save_log(char *str)
{
	write(fd, str, strlen(str));
}

void save_time(double seconds)
{
	char str[MAX_LEN];
	sprintf(str, "%f [s]\n", seconds);
	save_log(str);
}

int save_output(int npipes, int *pipe, int fd)
{
	int status;
	pid_t pid = fork();

	if(pid < 0) {
		ShellError("Can't fork()");
		return pid;
	}
	else if(pid == 0) {
		close(pipe[1]);
		if(dup2(pipe[0], 0) == -1)  ShellError("Can't dup() STDIN");
		close(pipe[0]);

		char aux[MAX_LEN];
		while(fgets(aux, MAX_LEN, stdin) != NULL) {
			save_log(aux);
			printf("%s", aux);
		}

		exit(0);
	}
	return pid;
}
