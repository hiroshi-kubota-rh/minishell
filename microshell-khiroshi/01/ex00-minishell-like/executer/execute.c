#include "minishell.h"

int	execute_file(int argc, char *argv[], char *exe_file)
{
	extern char **environ;
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0); //waitpidはpidを返すが，これはエラー処理の対象になる場合があるので注意
		return WEXITSTATUS(status);
	}
	else if (pid == 0)
	{
		execve(exe_file, &argv[0], environ);
		exit(0);
	}
	else
	{
		write(1, "error\n", 6);
		return (1);
	}
}

char *can_execute(char *argv)
{
	extern t_minishell		g_shell;
	char 	**paths;
	char	*tmp;
	char	*exe;
	int i = 0;

	paths = ft_split(get_value(g_shell.env, "PATH"), ':');
	while (paths[i] != NULL)
	{
		tmp = strjoin(paths[i], "/");
		exe = strjoin(tmp, argv);
		free(tmp);
		if (access(exe, X_OK) == 0)
			return (exe);
		i++;
	}
	return NULL;
}
