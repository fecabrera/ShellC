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
