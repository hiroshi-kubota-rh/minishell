#include "minishell.h"

void	env_delete(t_env *env, t_env *target)
{
	t_env *prev;

	while (env != NULL)
	{
		prev = env;
		env = env->next;
		if (env == target)
			break;
	}
	prev->next = target->next;
	free(target->value);
	free(target->key);
	free(target);
	return ;
}

void builtin_unset(int argc,char **argv)
{
	extern t_minishell g_shell;
	int	i;
	char **s;
	t_env *tmp;

	i = 1;
	while (i < argc)
	{
		s = split_by_first_c(argv[i], '=');
		tmp = find_by_key(g_shell.env, s[0]);
		if (tmp == NULL)
			continue ;
		else
		{
			env_delete(g_shell.env, tmp);
		}
		i++;
	}
}

