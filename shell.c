#include "ShellC.h"
#include <time.h>
#include <sys/stat.h>

const char *dir_list[] = { "", "/bin/", "/sbin/" };

int main()
{
	printf("\n#### ShellC ####\n");
	signal (SIGINT, SIG_IGN);
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	const char *user = pw->pw_name;
	mkdir("Log", S_IRWXU);
	while(1) {
		char *cwd = getcwd(NULL, 0);
		char cwd2[MAX_LEN];
		get_dir(homedir, cwd, cwd2);
		fd = open("Log/mishell.log", O_CREAT | O_RDWR | O_APPEND);
		printf("%s@ShellC:%s$ ", user, cwd2);
		free(cwd);
		char str[MAX_LEN];
		char *pipes[MAX_ARGS];
		int i;
		fgets(str, MAX_LEN, stdin);
		save_log(str);

		int npipes = parse(str, pipes, "|");
		int p[MAX_ARGS+1][2];

		for(i = 0; i < npipes; i++) pipe(p[i + 1]);
		long start = clock();

		// Executing each pipe
		for(i = 0; i < npipes; i++) {
			//printf("%d/%d: %s\n", i+1, npipes, pipes[i]);
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
			else if(!strcmp(argv[0], "rmlog")) {
				close(fd);
				remove("Log/mishell.log");
			}
			else if(!strcmp(argv[0], "help")) {
				int a;
				if(i == npipes - 1) a = save_output(npipes, p[i + 1], fd);
				pid_t pid = fork();
				if(pid == 0) {
					close(p[i + 1][0]);
					if(dup2(p[i+1][1], 1) == -1) ShellError("Can't dup() STDOUT");
					close(p[i+1][1]);
					printf("ShellC internal commands:\n");
					printf("\tcd: Change current working directory\n");
					printf("\trmlog: Remove log files\n");
					printf("\thelp: Print help\n");
					exit(0);
				}
				else {
					waitpid(-1, &pid, 0);
					close(p[i + 1][1]);
				}
				if(i == npipes - 1) waitpid(-1, &a, 0);
			}
			else {
				int a;
				if(i == npipes - 1) a = save_output(npipes, p[i + 1], fd);
				run_cmd(argv, i + 1, npipes, p[i], p[i + 1]);
				if(i == npipes - 1) waitpid(-1, &a, 0);
			}
		}
		double end = clock();
		save_time(((double)end - start) / CLOCKS_PER_SEC);
		close(fd);
	}
	return 0;
}
