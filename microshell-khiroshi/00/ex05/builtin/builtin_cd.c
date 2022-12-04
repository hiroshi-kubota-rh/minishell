#include "minishell.h"

void	builtin_cd(int argc, char **argv)
{
	if (argc > 2)
		printf("cd: too many arguments\n");
	else if (argc < 2)
		printf("cd: not enough arguments\n");
	if (access(argv[1], X_OK) != 0 || chdir(argv[1]) != 0)
		printf("cd: %s: %s\n", strerror(errno), argv[1]);
	return ;
}