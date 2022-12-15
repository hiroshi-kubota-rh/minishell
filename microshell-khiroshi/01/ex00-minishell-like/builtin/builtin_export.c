#include "minishell.h"

void	builtin_export(int argc, char **argv)
{
	extern t_minishell g_shell;
	int i;
	t_env *tmp;
	char	**s;

	if (argc <= 1)
		printf("export: not enough arguments\n");
	i = 1;
	while (i < argc)
	{
		s = split_by_first_c(argv[i], '=');
		if (argv[i][0] == '=')
			printf("export: error\n"); //bashだと　"bash: export: `=b': not a valid identifier"　みたいなエラー
		tmp = find_by_key(g_shell.env, s[0]);
		if(tmp != NULL)
		{
			if (s[1] != NULL)
			{
				tmp->value = s[1];
				tmp->is_shell_env = false;
			}
			else
				tmp->is_shell_env = false;
			free(s[0]);
			free(s);
		}
		else
		{
			tmp = new_env_node(argv[i]);
			env_list_add_last(&(g_shell.env), tmp);
		}
		i++;
	}

}