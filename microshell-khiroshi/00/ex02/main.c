#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/errno.h>

//gcc is_long.c split.c main.c -lreadlineでコンパイルする必要がある．

int		box_num(char const *s, char c);
char	**ft_split(char const *s, char c);
bool	is_long(char *s);

static int get_eight_bit_num(char *s)
{
	int re;
	unsigned char c;

	re = atoi(s);
	c = (unsigned char)(re);
	return (c - '\0');
}

void	builtin_exit(int argc, char **argv)
{
	int	eight_bit_num;

	if (argc >= 3)
	{
		printf("bash: exit: too many arguments");
		exit(1);
	}
	if (argc == 1)
		exit (0);
	if (is_long(argv[1]) == false)
	{
		printf("bash: exit: %s: numeric argument required", argv[1]);
		exit(255);
	}
	else
	{
		eight_bit_num = get_eight_bit_num(argv[1]);
		exit(eight_bit_num);
	}
}

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

int main(void)
{
	char	*line;
	char	**argv;
	int		argc;

	while (1)
	{
		line = readline("myshell> ");
		if (line == NULL)
		{
			free(line);
			exit(1);
		}
		argc = box_num(line, ' ');
		argv = ft_split(line, ' ');
		if (argc == 0)
			continue;
		else if (strncmp(argv[0], "exit", 5) == 0)
			builtin_exit(argc, argv);
		else if (strncmp(argv[0], "echo", 5) == 0)
			builtin_echo(argc, argv);
		else if (strncmp(argv[0], "cd", 3) == 0)
			builtin_cd(argc, argv);
		else if (strncmp(argv[0], "pwd", 4) == 0)
			builtin_pwd(argc, argv);
		else
			printf("builtin not found: %s\n", line);
		add_history(line);
		free(line);
	}
}