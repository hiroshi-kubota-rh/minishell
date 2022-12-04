#include "minishell.h"

void	init_minishell()
{
	extern t_minishell	g_shell;

	//envをコピーする．
	g_shell.env = dup_env();
}