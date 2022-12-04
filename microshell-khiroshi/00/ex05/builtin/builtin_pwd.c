#include "minishell.h"

void	builtin_pwd(int argc, char **argv)
{
	(void)argv;
	char *absolute_path;

	if (argc != 1)
		printf("pwd: too many arguments\n");
	else
	{
		absolute_path = getcwd(NULL, 0);
		printf("%s\n", absolute_path);
		free(absolute_path);
	}
	return ;
}