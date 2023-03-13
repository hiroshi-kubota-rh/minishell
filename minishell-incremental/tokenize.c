#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "minishell.h"

__attribute__((noreturn))
void	fatal(const char *msg);

void	*or_exit(void *p);

t_token	*token_new(char *word, t_e_tkind kind)
{
	t_token	*tok;

	tok = or_exit(calloc(1, sizeof(t_token)));
	tok->word = word;
	tok->kind = kind;
	tok->next = NULL;
	return (tok);
}

bool	ft_isblank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	consume_blank(const char **rest, const char *line)
{
	if (!ft_isblank(*line))
	{
		*rest = line;
		return (false);
	}
	while (ft_isblank(*line))
		line++;
	*rest = line;
	return (true);
}

const char	*is_operator(const char *s)
{
	static const char	*operators[] = {">>", ">", "<<", "<", "||", "&&", "|", ";", "\n", "(", ")",};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		if (!strncmp(s, operators[i], strlen(operators[i])))
			return (operators[i]);
		i++;
	}
	return (NULL);
}

t_token	*token_operator(const char **rest, const char *line)
{
	const char	*op;

	op = is_operator(line);
	if (!op)
		exit((dprintf(2, "unexpected token\n"), 255));
	*rest = &line[strlen(op)];
	return (token_new(or_exit(strdup(op)), TK_OP));
}

char	is_metachar(char c)
{
	if (c && strchr("|&;()<>\t ", c))
		return (c);
	return ('\0');
}
bool	is_word(const char *s)
{
	return (*s && !is_metachar(*s));
}

t_token	*token_word(const char **rest, const char *line)
{
	size_t	i;
	int		is_quoted;

	i = 0;
	is_quoted = 0;
	while (line[i] && (is_quoted || !is_metachar(line[i])))
	{
		if (!(is_quoted & 2) && line[i] == '\'')
			is_quoted ^= 1;
		else if (!(is_quoted & 1) && line[i] == '\"')
			is_quoted ^= 2;
		i++;
	}
	*rest = &line[i];
	return (token_new(or_exit(strndup(line, i)), TK_WORD));
}

t_token	*tokenize(const char *line)
{
	t_token	head;
	t_token	*tok;

	tok = &head;
	while (line && *line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line))
			tok->next = token_operator(&line, line);
		else if (is_word(line))
			tok->next = token_word(&line, line);
		else
			exit((dprintf(2, "todo: unexpected token [%c]\n", *line), -1));
		tok = tok->next;
	}
	tok->next = token_new(NULL, TK_EOF);
	return (head.next);
}

char	*str_append(char *s, char c)
{
	size_t	len;
	char	*dst;

	if (!s)
	{
		dst = or_exit(strdup((char[2]){c}));
		return (dst);
	}
	len = strlen(s);
	dst = or_exit(malloc(len + 2));
	strlcpy(dst, s, len + 1);
	dst[len] = c;
	dst[len + 1] = '\0';
	free(s);
	return (dst);
}

char	*str_unquote(const char *s)
{
	char	*dst;
	size_t	i;
	int		is_quoted;

	dst = str_append(NULL, '\0');
	i = 0;
	is_quoted = 0;
	while (s[i] && (is_quoted || !is_metachar(s[i])))
	{
		if (!(is_quoted & 2) && s[i] == '\'')
			is_quoted ^= 1;
		else if (!(is_quoted & 1) && s[i] == '\"')
			is_quoted ^= 2;
		else
			dst = str_append(dst, s[i]);
		i++;
	}
	return (dst);
}

void	*free_assign(void *oldp, void *newp)
{
	free(oldp);
	return (newp);
}

void	remove_quote(t_token *tok)
{
	t_token	*t;

	t = tok;
	while (t && t->kind != TK_EOF)
	{
		if (t->kind == TK_WORD)
		{
			t->word = free_assign(t->word, str_unquote(t->word));
		}
		t = t->next;
	}
}

t_node	*expand(t_node *node)
{
	remove_quote(node->args);
	return (node);
}

size_t	token_len(t_token *tok)
{
	size_t	i;
	t_token	*t;

	t = tok;
	i = 0;
	while (t && t->kind != TK_EOF)
	{
		i++;
		t = t->next;
	}
	return (i);
}

char	**token_to_argv(t_token *tok)
{
	size_t	i;
	t_token	*t;
	char	**argv;

	argv = or_exit(calloc(sizeof(char *), (token_len(tok) + 1)));
	i = 0;
	t = tok;
	while (t && t->kind != TK_EOF)
	{
		dprintf(2, "[%s]", t->word);
		argv[i] = t->word;
		i++;
		t = t->next;
	}
	dprintf(2, "\n");
	return (argv);
}
