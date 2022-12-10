#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t	ft_wordcount(char const *s, int issep());
char	*ft_strcdup(char const *s, int issep());
char	**ft_split_func(char const *s, int issep());
void	*ft_free_split(char **arr);

int	error_exit(const char *s)
{
	dprintf(2, "error: %s\n", s);
	return (exit(1), 1);
}

typedef struct s_pipe
{
	int	fd[2];
}	t_pipe;

int	exec_pipes(int argc, char **argv)
{
	size_t	i;
	pid_t	pid;
	t_pipe	p[argc];

	i = -1;
	while (++i < (size_t)argc)
	{
		char	**av = ft_split_func(argv[i], isspace);
		p[i] = (t_pipe){};
		if (i < (size_t)argc-1)
			pipe(p[i].fd);
		pid = fork();
		if (pid < 0)
			error_exit("fork");
		else if (pid == 0)
		{
			if (i < (size_t)argc - 1)
			{
				dup2(p[i].fd[1], 1);
				close(p[i].fd[1]);
			}
			if (i > 0)
			{
				dup2(p[i-1].fd[0], 0);
				close(p[i-1].fd[0]);
			}
			execvp(av[0], av);
			dprintf(2, "command not found: %s\n", av[0]);
			exit(1);
		}
		else
		{
				//close(p[i-1].fd[0]);
				close(p[i].fd[1]);
			ft_free_split(av);
		}
	}
	i = -1;
	while (++i < (size_t)argc)
	{
		int	status;
		wait(&status);
		dprintf(2, "command: [%s] $?=%d sig=%d\n", argv[i], WEXITSTATUS(status), WTERMSIG(status));
	}
	return (0);
}
