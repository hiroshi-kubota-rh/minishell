#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "dict.h"

#if 1
typedef struct s_env	t_env;
struct s_env {
	char	*name;
	char	*value;
	bool	is_env;
	t_env	*next;
};
#endif

t_dict	g_env;

char	*ft_strcdup(char const *s, int issep(char));
char	**ft_split_func_n(char const *s, bool issep(), size_t n);

#if 0
int	env_replace(t_env *e, char const *name, char const *value)
{
	while (e)
	{
		if (!strcmp(e->name, name))
		{
			free(e->value);
			if (!value)
				e->value = NULL;
			else
				e->value = strdup(value);
			return (1);
		}
		e = e->next;
	}
	return (0);
}

t_env	*env_append(t_env *e, t_env *next)
{
	t_env *const	head = e;

	if (!e)
		return (next);
	if (env_replace(e, next->name, next->value))
	{
		free(next->name);
		free(next->value);
		free(next);
		return (head);
	}
	while (e->next)
	{
		e = e->next;
	}
	e->next = next;
	return (head);
}
#endif

static int	issep(char c)
{
	return (c == '=');
}

bool	is_valid_identifier(char *s)
{
	size_t	i;

	if (!(isalpha(*s) || (*s == '_')))
		return (false);
	i = 0;
	while (s[++i])
	{
		if (!(isalnum(*s) || (*s == '_')))
			return (false);
	}
	return (true);
}

t_env	str_to_env(char const *s)
{
	char	*name = ft_strcdup(s, issep);
	char	*pos_eq = strchr(s, '=');
	char	*value;
	t_env	e;

	if (!name[0] || !is_valid_identifier(name))
	{
		free(name);
		return ((t_env){});
	}
	if (pos_eq)
		value = strdup(pos_eq + 1);
	else
		value = NULL;
	e = (t_env){name, value, !!pos_eq, NULL};
	return (e);
}

bool	env_generate(t_dict *dict, char **environ)
{
	size_t	i;
	t_env	e;

	i = 0;
	while (environ[i])
	{
		e = str_to_env(environ[i]);
		if (!e.name)
			printf("export: %s: not a valid identifier\n", environ[i]);
		else if (!dict_insert(dict, e.name, e.value))
			return (false);
		i++;
	}
	return (true);
}

static void	env_print(const t_dict *dict, const char *prefix)
{
	size_t	i;
	t_entry	e;

	i = 0;
	while (i < dict->cap)
	{
		e = dict->ptr[i++];
		if (e.key && e.val)
			printf("%s%s=%s\n", prefix, e.key, e.val);
		else if (e.key && prefix[0])
			printf("%s%s\n", prefix, e.key);
	}
}

int	builtin_env(int argc, char **argv)
{
	extern char	**environ;

	(void)argv;
	if (argc > 1 && printf("env: too many arguments\n"))
		return (1);
#if 1
	env_print(&g_env, "");
#else
	size_t		i;
	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);
#endif
	return (0);
}

int	builtin_export(int argc, char **argv)
{
	extern char	**environ;

	if (!g_env.len)
		env_generate(&g_env, environ);
	if (argc <= 1)
		return (env_print(&g_env, "declare -x "), 0);
	env_generate(&g_env, &argv[1]);
	return (0);
}

int	builtin_unset(int argc, char **argv)
{
	size_t		i;
	t_entry		*e;

	if (argc <= 1 && printf("unset: not enough arguments\n"))
		return (1);
	i = 1;
	while (argv[i])
	{
		e = dict_search(&g_env, argv[i]);
		if (e)
		{
			free(e->key);
			free(e->val);
			*e = (t_entry){};
		}
		i++;
	}
	return (0);
}
