#include <stdlib.h>
#include <stdio.h>

__attribute__((noreturn))
void	fatal(const char *msg)
{
	dprintf(2, "error: %s\n",  msg);
	exit(1);
}

void	*or_exit(void *p)
{
	if (p)
		return (p);
	fatal("malloc");
}

