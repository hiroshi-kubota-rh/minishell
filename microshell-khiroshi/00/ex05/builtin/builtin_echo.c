#include "minishell.h"

void	builtin_echo(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i != argc - 1)
			printf(" ");
		i++;
	}
	printf("\n");
	return ;
}