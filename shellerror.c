#include "ShellC.h"

void ShellError(const char *str)
{
	fprintf(stderr, "*** Error: %s\n", str);
}

void CommandNotFound(const char *cmd)
{
	fprintf(stderr, "*** Error: Command '%s' uknown\n", cmd);
}