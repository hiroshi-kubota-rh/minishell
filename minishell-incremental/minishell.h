#ifndef MINISHELL_H
# define MINISHELL_H

enum e_token_kind {
	TK_BEGIN = 0,
	TK_WORD,
	TK_RESERVED,
	TK_OP,
/*
	TK_RD_APP,
	TK_RD_OUT,
	TK_RD_HEREDOC,
	TK_RD_IN,
	TK_AND,
	TK_OR,
	TK_PARENL,
	TK_PARENR,
	TK_PIPE,
	TK_SEMICOLON,
*/
	TK_EOF,
};
typedef enum e_token_kind	t_e_tkind;

typedef struct s_token	t_token;
struct	s_token {
	t_token		*next;
	char		*word;
	t_e_tkind	kind;
};

enum e_node_kind {
	NK_SIMPLECMD,
};
typedef enum e_node_kind	t_e_nkind;

typedef int	t_fd;

typedef struct s_redir	t_redir;
struct	s_redir {
	t_redir		*next;
	const char	*filename;
	t_fd		file_fd;
	t_fd		target_fd;
	t_fd		stash_fd;
};

typedef struct s_node	t_node;
struct	s_node {
	t_node		*next;
	t_token		*args;
	t_e_nkind	kind;

	t_redir		*redirect;
};

#endif //MINISHELL_H
