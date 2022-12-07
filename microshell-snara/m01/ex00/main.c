#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <readline/readline.h>

size_t	ft_wordcount(char const *s, int issep());
char	*ft_strcdup(char const *s, int issep());
char	**ft_split_func(char const *s, int issep());
void	*ft_free_split(char **arr);

int	ft_system(const char *cmd)
{
	extern char	**environ;
	pid_t		pid;
	int			status;
	char		**argv = (char *[]){"sh", "-c", (char *)cmd, NULL};

	pid = fork();
	if (pid == -1)
	{
		printf("fork() failed\n");
		return (-1);
	}
	if (pid == 0)
	{
		execve("/bin/sh", argv, environ);
		printf("execve() failed\n");
		exit(-1);
	}
	pid = waitpid(pid, &status, 0);
	if (pid == -1)
	{
		printf("wait() failed\n");
		return (-1);
	}
	return (status);
}

int	exec_abspath(int argc, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	int			status;
	struct stat	st;

	(void)argc;
	if (((stat(argv[0], &st) != 0) && printf("command not found: %s\n", argv[0]))
		|| (!(st.st_mode & S_IXUSR) && printf("permission denied: %s\n", argv[0]))
		|| (S_ISDIR(st.st_mode) && printf("is a directory: %s\n", argv[0]))
	)
		return (1);
	pid = fork();
	if (pid == -1 && printf("fork() failed\n"))
		return (-1);
	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		printf("execve() failed: "), perror(argv[0]);
		exit(1);
	}
	pid = waitpid(pid, &status, 0);
	if (pid == -1 && (perror("waitpid() failed"), 1))
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

static int	microshell(void)
{
	char	*line;
	int		argc;
	char	**argv;

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
		int status = exec_abspath(argc, argv);
		printf("$?=%d\n", status);
		argv = ft_free_split(argv);
	}
	return (0);
}

__attribute__((constructor)) void	constructor(void)
{
	errno = 0;
}

int	main(void)
{
	microshell();
	return (0);
}
