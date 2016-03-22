#include "ShellC.h"

int get_dir(const char *home, const char *path, char *str)
{
	int n = strlen(home), m = strlen(path), i;
	for(i = 0; i < n; i++) {
		if(home[i] != path[i]) {
			strcpy(str, path);
			return 1;
		}
	}
	sprintf(str, "~%s", path + i);
	return 0;
}