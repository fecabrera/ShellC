#include "ShellC.h"
#include <time.h>

const char *dir_list[] = { "", "/bin/", "/sbin/" };

int main()
{
	printf("\n#### ShellC ####\n");
	signal (SIGINT, SIG_IGN);
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	const char *user = pw->pw_name;
	fd = open("mishell.log", O_CREAT | O_WRONLY | O_APPEND);
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
		save_log(str);
		int npipes = parse(str, pipes, "|");
		int p[MAX_ARGS+1][2];
		double start = clock();
		for(i = 0; pipes[i] != NULL; i++) {
			//printf("%d/%d: %s\n", i+1, npipes, pipes[i]);
			pipe(p[i+1]);
			char *argv[MAX_ARGS];
			parse(pipes[i], argv, " \t\n");
			if(argv[0] == NULL) continue;
			else if(!strcmp(argv[0], "exit")) {
				close(fd);
				exit(0);
			}
			else if(!strcmp(argv[0], "cd")) {
				if(argv[1] != NULL) chdir(argv[1]);
			}
			else if(!strcmp(argv[0], "slog")) {

			}
			else run_cmd(argv, i+1, npipes, p[i], p[i+1]);
		}
		double end = clock();
		save_time(((double)end-start) / CLOCKS_PER_SEC);
	}
	return 0;
}
