#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>

size_t	ft_wordcount(char const *s, int issep(int));
char	**ft_split_func(char const *s, int issep(int));
void	*ft_free_split(char **arr);

static void	builtin_exit(char **argv)
{
	long	status;
	size_t	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	status = 0;
	if (argc >= 2 && sscanf(argv[1], "%ld", &status) != 1
		&& printf("exit: numeric arguments required\n"))
		exit(2);
	if (argc > 2
		&& printf("exit: too many arguments\n"))
		return ;
	exit(status);
}

static void	builtin_echo(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		printf("%*s%s", i > 1, "", argv[i]);
		i++;
	}
	printf("\n");
}

static void	microshell(void)
{
	char	*line;
	char	**argv;

	line = NULL;
	while (free(line), 1)
	{
		line = readline("$> ");
		if (!line)
			exit(1);
		else if (ft_wordcount(line, isspace) == 0)
			continue ;
		add_history(line);
		argv = ft_split_func(line, isspace);
		if (!strcmp(argv[0], "exit"))
			builtin_exit(argv);
		else if (!strcmp(argv[0], "echo"))
			builtin_echo(argv);
		else
			printf("builtin not found: %s\n", line);
		ft_free_split(argv);
	}
}

int	main(void)
{
	microshell();
	return (0);
}
