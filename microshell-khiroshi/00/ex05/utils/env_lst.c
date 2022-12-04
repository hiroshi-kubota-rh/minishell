#include "minishell.h"

void	update_value(t_env *env, char *new_value)
{
	char	*old_value;

	old_value = env->value;
	env->value = new_value;
	free(old_value);
	return ;
}

t_env	*find_by_key(t_env *env, char *search_key)
{
	while (env != NULL)
	{
		if (strcmp(env->key, search_key) == 0)
		{
			return env;
		}
		env = env->next;
	}
	return NULL;
}

t_env	*new_env_node(char *s)
{
	char **str;
	t_env *env;

	str = split_by_first_c(s, '=');
	if (str == NULL)
		return NULL;
	env = (t_env*) xmalloc(sizeof(t_env));
	env->key = str[0];
	if (str[1] != NULL)
	{
		env->is_shell_env = false;
		env->value = str[1];
	}
	else
		env->is_shell_env = true;
	return env;
}

t_env	*envlast(t_env *env)
{
	if (env == NULL)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

void	env_list_add_last(t_env **env, t_env *new)
{
	if (env == NULL)
		return ;
	if (*env == NULL)
		*env = new;
	envlast(*env)->next = new;
	new->next = NULL;
}