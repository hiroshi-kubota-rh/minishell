#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>

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
		else
		{
			add_history(line);
			printf("builtin not found: %s\n", line);
			free(line);
		}
	}
}