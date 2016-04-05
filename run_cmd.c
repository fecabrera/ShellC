#include "ShellC.h"

int run_cmd(char *argv[], int index, int npipes, int *in_pipe, int *out_pipe)
{
	int status;
	pid_t pid = fork();

	if(pid < 0) {
		ShellError("Can't fork()");
		return pid;
	}
	else if(pid == 0) {
		if(index != 1) {
			close(in_pipe[1]);
			if(dup2(in_pipe[0], 0) == -1)  ShellError("Can't dup() STDIN");
			close(in_pipe[0]);
		}
		//if(index != npipes) {
			close(out_pipe[0]);
			if(dup2(out_pipe[1], 1) == -1) ShellError("Can't dup() STDOUT");
			close(out_pipe[1]);
		//}

		char cmd[MAX_LEN];
		int i=0;
		while(i < 3) {
			sprintf(cmd, "%s%s", dir_list[i], argv[0]);
			execvp(cmd, argv);
			i++;
		}
		CommandNotFound(argv[0]);
	}
	else {
		waitpid(-1, &pid, 0);
		close(out_pipe[1]);
	}

	return 0;
}
