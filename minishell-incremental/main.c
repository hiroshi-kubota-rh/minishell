#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ERROR_SYNTAX 2

typedef struct s_token	t_token;
t_token	*tokenize(const char *line);
t_token	*expand(t_token *tok);
char	**token_to_argv(t_token *tok);
int	exec(char *argv[]);

int	g_status = 0;

void	init()
{
	rl_outstream = stderr;
}

int	interpret(char *line)
{
	t_token	*tok;
	char	**argv;

	tok = tokenize(line);
	if (!tok)
		g_status = ERROR_SYNTAX;
	tok = expand(tok);
	argv = token_to_argv(tok);
	g_status = exec(argv);
	return (g_status);
}

void	loop()
{
	char		*line;

	line = readline("minishell$ ");
	if (!line)
		exit(g_status);
	if (line[0])
	{
		add_history(line);
		interpret(line);
		dprintf(2, "$?=%d\n", g_status);
	}
	free(line);
	line = NULL;
}

int	main()
{
	init();
	while (1)
	{
		loop();
	}
}
