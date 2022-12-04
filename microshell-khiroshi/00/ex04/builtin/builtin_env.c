#include "minishell.h"

void	builtin_env(int argc, char **argv)
{
	int	i;
	extern t_minishell	g_shell;
	t_env	*env;

	env = g_shell.env;
	if (argc > 2)
		printf("env: %s: No such file or directory", argv[1]);
	i = 0;
	while (env != NULL)
	{
		if (env->is_shell_env == true)
			continue;
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return ;
}
