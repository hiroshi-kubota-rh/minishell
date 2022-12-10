#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

int	exec_abspath(char *path, int argc, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	int			status;
	struct stat	st;

	(void)argc;
	if (((stat(path, &st)) && printf("command not found: %s\n", argv[0]))
		|| (!(st.st_mode & S_IXUSR) && printf("permission denied: %s\n", argv[0]))
		|| (S_ISDIR(st.st_mode) && printf("is a directory: %s\n", argv[0]))
	)
		return (1);
	pid = fork();
	if (pid == -1 && printf("fork() failed\n"))
		return (-1);
	if (pid == 0)
	{
		execve(path, argv, environ);
		printf("execve() failed: "), perror(path);
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

static int iscolon(int c)
{
	return (c == ':');
}
int	exec_relpath(int argc, char **argv)
{
	extern char	**environ;
	char		**paths;
	size_t		i;
	struct stat	st;

	if (strchr(argv[0], '/'))
		return (exec_abspath(argv[0], argc, argv));
	paths = ft_split_func(getenv("PATH"), iscolon);
	i = 0;
	while (paths && paths[i])
	{
		char	*path;
		asprintf(&path, "%s/%s", paths[i], argv[0]);
		//printf("%s\n", path);
		if ((!stat(path, &st) && (st.st_mode & S_IXUSR) && !S_ISDIR(st.st_mode)))
		{
			int status = exec_abspath(path, argc, argv);
			return (free(path), status);
		}
		free(path);
		i++;
	}
	paths = ft_free_split(paths);
	printf("command not found: %s\n", argv[0]);
	return (1);
}

static int	ispipe(int c)
{
	return (c == '|');
}
int	exec_pipes(int argc, char **argv);
int	microshell(void)
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
		argc = ft_wordcount(line, ispipe);
		if (argc == 0)
			continue ;
		add_history(line);
		argv = ft_split_func(line, ispipe);
		//int status = exec_relpath(argc, argv);
		int status = exec_pipes(argc, argv);
		printf("$?=%d\n", status);
		argv = ft_free_split(argv);
	}
	return (0);
}

__attribute__((constructor)) void	constructor(void)
{
	errno = 0;
}

int	main(int argc, char **argv)
{
	//exec_pipes(argc-1, &argv[1]);
	microshell();
	return (0);
}
