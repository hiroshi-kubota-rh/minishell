#include <stddef.h>
#include <stdbool.h>
#include <sys/param.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>

size_t	ft_wordcount(char const *s, int issep(int));
char	**ft_split_func(char const *s, int issep(int));
void	*ft_free_split(char **arr);

static int	builtin_exit(int argc, char **argv, long status)
{
	if (argc >= 2 && sscanf(argv[1], "%ld", &status) != 1
		&& printf("exit: numeric arguments required\n"))
		exit(2);
	if (argc > 2
		&& printf("exit: too many arguments\n"))
		return (1);
	exit(status);
}

static int	builtin_echo(int argc, char **argv)
{
	size_t	i;

	(void)argc;
	i = 1;
	while (argv[i])
	{
		printf("%*s%s", i > 1, "", argv[i]);
		i++;
	}
	printf("\n");
	return (0);
}

static int	builtin_cd(int argc, char **argv)
{
	if ((argc > 2 && printf("cd: too many arguments\n"))
		|| (argc < 2 && printf("cd: not enough arguments\n")))
		return (1);
	if ((access(argv[1], X_OK) != 0 || chdir(argv[1]) != 0)
		&& printf("cd: %s: %s\n", strerror(errno), argv[1]))
		return (1);
	return (0);
}

static int	builtin_pwd(int argc, char **argv)
{
	char	*path;

	(void)argv;
	if (argc > 1 && printf("pwd: too many arguments\n"))
		return (1);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	return (0);
}

static int	builtin_env(int argc, char **argv)
{
	extern char	**environ;
	size_t	i;

	(void)argv;
	if (argc > 1 && printf("env: too many arguments\n"))
		return (1);
	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);
	return (0);
}

static int	microshell(void)
{
	long	status;
	char	*line;
	int		argc;
	char	**argv;

	status = 0;
	line = NULL;
	while (free(line), 1)
	{
		line = readline("$> ");
		if (!line)
			exit(1);
		argc = ft_wordcount(line, isspace);
		if (argc == 0)
			continue ;
		add_history(line);
		argv = ft_split_func(line, isspace);
		if (!strcmp(argv[0], "exit"))
			status = builtin_exit(argc, argv, status);
		else if (!strcmp(argv[0], "echo"))
			status = builtin_echo(argc, argv);
		else if (!strcmp(argv[0], "cd"))
			status = builtin_cd(argc, argv);
		else if (!strcmp(argv[0], "pwd"))
			status = builtin_pwd(argc, argv);
		else if (!strcmp(argv[0], "env"))
			status = builtin_env(argc, argv);
		else
			status = printf("builtin not found: %s\n", line) || 1;
		argv = ft_free_split(argv);
	}
	return (0);
}

int	main(void)
{
	microshell();
	return (0);
}
