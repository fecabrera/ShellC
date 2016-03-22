#include "ShellC.h"

int run_cmd(char *argv[], int index, int npipes)
{
	int status;
	int p[2];
	pid_t pid = fork();
	pipe(p);

	if(pid < 0) {
		fprintf(stderr, "*** Error: can't fork()\n");
		return pid;
	}
	else if(pid == 0) {
		if(index!=1) dup2(p[0], 0);
		if(index!=npipes) dup2(p[1], 1);
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
