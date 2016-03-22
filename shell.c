#include "ShellC.h"

const char *dir_list[] = { "", "/bin/", "/sbin/" };

int main()
{
	signal (SIGINT, SIG_IGN);
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	const char *user = pw->pw_name;
	while(1) {
		char *cwd = getcwd(NULL, 0);
		char cwd2[MAX_LEN];
		get_dir(homedir, cwd, cwd2);
		printf("%s@ShellC:%s$ ", user, cwd2);
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
