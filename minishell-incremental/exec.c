#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

__attribute__((noreturn))
void	fatal(const char *msg)
{
	dprintf(2, "error: %s\n",  msg);
	exit(1);
}

void	*or_exit(void *p)
{
	if (p)
		return (p);
	fatal("malloc");
}

size_t	ft_strnclen(const char *s, size_t n, char c)
{
	size_t	i;

	i = 0;
	while (i < n && s[i] != c && s[i])
	{
		i++;
	}
	return (i);
}

char	*search_path(const char *name)
{
	static char	path[PATH_MAX + 1] = "";
	char		*val;
	size_t		len;

	val = getenv("PATH");
	if (!val)
	{
		strlcpy(path, name, PATH_MAX);
		return (path);
	}
	while (*val)
	{
		len = ft_strnclen(val, PATH_MAX, ':');
		strlcpy(path, val, len + 1);
		strlcat(path, "/", PATH_MAX);
		strlcat(path, name, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (or_exit(strdup(path)));
		val = &val[len + 1];
	}
	return (NULL);
}

__attribute__((noreturn))
int	exec_child(char *argv[])
{
	extern char	**environ;
	char		*path;
	struct stat	st;

	path = argv[0];
	if (path && !strchr(path, '/'))
	{
		path = search_path(path);
		if (!path || !path[0] || access(path, F_OK) < 0)
			exit((dprintf(2, "minishell: %s: %s\n", argv[0], "command not found"), 127));
		if (access(path, X_OK) < 0)
			exit((dprintf(2, "minishell: %s: %s\n", argv[0], "permission denied"), 126));
		if (stat(path, &st) < 0)
			exit((dprintf(2, "minishell: %s: %s\n", argv[0], "stat failed"), 127));
		if (S_ISDIR(st.st_mode))
			exit((dprintf(2, "minishell: %s: %s\n", argv[0], "is a directory"), 126));
	}
	else if (path)
	{
		if (access(path, F_OK) < 0)
			exit((dprintf(2, "minishell: %s: %s\n", argv[0], "no such file or directory"), 127));
		if (access(path, X_OK) < 0)
			exit((dprintf(2, "minishell: %s: %s\n", argv[0], "permission denied"), 126));
		if (stat(path, &st) < 0)
			exit((dprintf(2, "minishell: %s: %s\n", argv[0], "stat failed"), 127));
		if (S_ISDIR(st.st_mode))
			exit((dprintf(2, "minishell: %s: %s\n", argv[0], "is a directory"), 126));
	}
	else
		fatal("path=NULL");
	execve(path, argv, environ);
	fatal("execve");
}

int	exec(char *argv[])
{
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal("fork");
	else if (pid == 0)
	{
		exec_child(argv);
	}
	else
	{
		waitpid(0, &wstatus, 0);
		if (WIFEXITED(wstatus))
			return (WEXITSTATUS(wstatus));
		if (WIFSIGNALED(wstatus))
			return (WTERMSIG(wstatus));
		return (wstatus);
	}
}

