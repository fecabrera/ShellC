#include "ShellC.h"

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
