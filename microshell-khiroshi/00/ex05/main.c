//gcc is_long.c split.c main.c -lreadlineでコンパイルする必要がある．
#include "include/minishell.h"

t_minishell		g_shell;

int main(void)
{
	char	*line;
	char	**argv;
	int		argc;

	init_minishell();
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
		else if (strncmp(argv[0], "env", 4) == 0)
			builtin_env(argc, argv);
		else if (strncmp(argv[0], "export", 7) == 0)
			builtin_export(argc, argv);
		else if (strncmp(argv[0], "unset", 6) == 0)
			builtin_unset(argc, argv);
		else
			printf("builtin not found: %s\n", line);
		add_history(line);
		free(line);
	}
}