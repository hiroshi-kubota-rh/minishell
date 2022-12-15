
#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/errno.h>
#include <limits.h>

#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>


typedef struct s_env
{
	char 			*key;
	char 			*value;
	bool			is_shell_env;
	struct s_env	*next;
}				t_env;

typedef struct s_minishell
{
	t_env	*env;
}   t_minishell;



//built_in
void	builtin_cd(int argc, char **argv);
void	builtin_echo(int argc, char **argv);
void	builtin_env(int argc, char **argv);
void	builtin_exit(int argc, char **argv);
void	builtin_pwd(int argc, char **argv);
void	builtin_export(int argc, char **argv);
void 	builtin_unset(int argc,char **argv);

//inint
t_env	*dup_env(void);
void	init_minishell();


//execute

char	*can_execute(char *argv);
int		execute_file(int argc, char *argv[], char *exe_file);

//util
bool	is_long(char *s);
int		box_num(char const *s, char c);
char	**ft_split(char const *s, char c);
char	**split_by_first_c(const char *str, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*strjoin(char const *s1, char const *s2);

void *xmalloc (size_t size);

t_env	*new_env_node(char *s);
t_env	*envlast(t_env *env);
void	env_list_add_last(t_env **env, t_env *new);
void	update_value(t_env *env, char *new_value);
t_env	*find_by_key(t_env *env, char *search_key);
char	*get_value(t_env *env, char *search_key);

#endif //MINISHELL_H
