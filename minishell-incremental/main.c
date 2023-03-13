#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"

#define ERROR_SYNTAX 2

t_token	*tokenize(const char *line);
t_node	*parse(t_token *tok);
t_node	*expand(t_node *tok);
int		exec(t_node *node);

int	g_status = 0;

void	init()
{
	rl_outstream = stderr;
}

int	interpret(char *line)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	node = parse(tok);
	if (g_status == ERROR_SYNTAX)
		return (g_status);
	node = expand(node);
	g_status = exec(node);
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
