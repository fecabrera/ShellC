#include "ShellC.h"

void cd(char *argv[])
{
	if(argv[1] != NULL) chdir(argv[1]);
}