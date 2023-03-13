#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "minishell.h"

__attribute__((noreturn))
void	fatal(const char *msg);

void	*or_exit(void *p);

t_token	*token_new(char *word, t_e_tkind kind);

extern int	g_status;

t_node	*node_new(t_e_nkind kind)
{
	t_node	*node;

	node = or_exit(calloc(1, sizeof(t_node)));
	node->kind = kind;
	return (node);
}

t_token	*token_dup(t_token *tok)
{
	char	*word;

	word = or_exit(strdup(tok->word));
	return (token_new(word, tok->kind));
}

void	token_append(t_token **head, t_token *tok)
{
	while (*head)
		head = &(*head)->next;
	*head = tok;
}

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 42);
	if (stashfd < 0)
		fatal("fcntl");
	if (close(fd) < 0)
		fatal("close");
	return (stashfd);
}
t_redir	*redirect_in(const char *name)
{
	t_redir	*re;
	t_fd	fd;

	re = or_exit(calloc(1, sizeof(t_redir)));
	re->target_fd = 0;
	re->next = NULL;
	re->filename = name;
	fd = open(name, O_RDONLY, 0644);
	if (fd < 0)
		fatal("could not open file");
	re->file_fd = fd;
	re->stash_fd = stashfd(re->target_fd);
	dup2(re->file_fd, re->target_fd);
	return re;
}
t_redir	*redirect_out(const char *name)
{
	t_redir	*re;
	t_fd	fd;

	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		fatal("could not open file");
	re = or_exit(calloc(1, sizeof(t_redir)));
	re->filename = name;
	re->target_fd = 1;
	re->file_fd = fd;
	re->next = NULL;
	re->stash_fd = stashfd(re->target_fd);
	dup2(re->file_fd, re->target_fd);
	return re;
}
t_redir	*redirect_app(const char *name)
{
	t_redir	*re;
	t_fd	fd;

	fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		fatal("could not open file");
	re = or_exit(calloc(1, sizeof(t_redir)));
	re->filename = name;
	re->target_fd = 1;
	re->file_fd = fd;
	re->next = NULL;
	re->stash_fd = stashfd(re->target_fd);
	dup2(re->file_fd, re->target_fd);
	return re;
}
t_redir	*redirect_push_front(t_redir **head, t_redir *re)
{
	re->next = *head;
	*head = re;
	return re;
}
void	redirect_reset(t_redir *re)
{
	while (re)
	{
		dup2(re->stash_fd, re->target_fd);
		re = re->next;
	}
}

t_node	*parse(t_token *tok)
{
	t_node	head;
	t_node	*node = &head;
	t_token	*t;

	node->next = node_new(NK_SIMPLECMD);
	node = node->next;
	t = tok;
	while (t && t->kind != TK_EOF)
	{
		dprintf(2, "[%s]", t->word);
		if (t->kind == TK_WORD)
			token_append(&node->args, token_dup(t));
#if 1
			//TODO
		else if (!strcmp(t->word, ">") && t->next->kind == TK_WORD)
		{
			redirect_push_front(&node->redirect, redirect_out(t->next->word));
			t = t->next->next;
			continue ;
		}
		else if (!strcmp(t->word, ">>") && t->next->kind == TK_WORD)
		{
			redirect_push_front(&node->redirect, redirect_app(t->next->word));
			t = t->next->next;
			continue ;
		}
		else if (!strcmp(t->word, "<") && t->next->kind == TK_WORD)
		{
			redirect_push_front(&node->redirect, redirect_in(t->next->word));
			t = t->next->next;
			continue ;
		}
#endif
		else if (!strcmp(t->word, "|"))
		{
			node->next = node_new(NK_SIMPLECMD);
			node = node->next;
		}
		else
			exit((dprintf(2, "todo: unexpected token [%s]\n", t->word), -1));
		t = t->next;
	}
	dprintf(2, "\n");
	return (head.next);
}
