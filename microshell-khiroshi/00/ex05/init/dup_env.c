#include "minishell.h"

t_env	*dup_env(void)
{
	extern char **environ;
	int 		i;
	t_env		*env;
	t_env		*tmp;

	env = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		tmp = new_env_node(environ[i]);
		env_list_add_last(&env, tmp);
		i++;
	}
	return env;
}