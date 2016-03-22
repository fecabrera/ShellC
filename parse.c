#include "ShellC.h"

int parse(char *str, char *argv[], const char* delim)
{
	int i = 0;
	argv[i] = strtok(str, delim);
	while(argv[i++] != NULL) {
		argv[i] = strtok(NULL, delim);
	}
	return i;
}