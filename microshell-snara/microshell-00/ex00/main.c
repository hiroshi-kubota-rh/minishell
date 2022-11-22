#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

static void	microshell()
{
	char	*line;

	while (1)
	{
		line = readline("$> ");
		if (!line)
			exit(1);
		else if (!strcmp(line, ""))
			;
		else if (!strcmp(line, "exit"))
			exit(0);
		else
			printf("builtin not found: %s\n", line);
		free(line);
	}
}

int	main(void)
{
	microshell();
	return (0);
}
