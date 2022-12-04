/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiroshi </var/mail/khiroshi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 00:51:30 by khiroshi          #+#    #+#             */
/*   Updated: 2022/11/12 01:00:02 by khiroshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(char const s, char c)
{
	if (s == c)
		return (1);
	else
		return (0);
}

int	box_num(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (check(s[j], c) == 0 && check(s[j + 1], c) == 1)
			i++;
		else if (check(s[j], c) == 0 && s[j + 1] == '\0')
			i++;
		j++;
	}
	return (i);
}

static char	*into_box(const char *s, char c, int i)
{
	char	*tmp;
	int		b;
	int		e;

	b = 0;
	e = 0;
	while (i-- >= 0)
	{
		b = b + e;
		e = 0;
		while (check(s[b], c) == 1)
			b++;
		while (check(s[b + e], c) == 0)
			e++;
	}
	tmp = (char *)malloc(sizeof(char) * (e + 1));
	if (tmp == NULL )
		return (NULL);
	tmp = memcpy(tmp, (s + b), e);
	tmp[e] = '\0';
	return (tmp);
}

char	**ft_split(char const *s, char c)
{
	char	**box;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	box = (char **)malloc(sizeof(char *) * (box_num(s, c) + 1));
	if (box == NULL)
		return (NULL);
	while (i < box_num(s, c))
	{
		box[i] = into_box(s, c, i);
		if (box[i] == NULL)
		{
			while (i >= 0)
				free(box[i--]);
			free(box);
			return (NULL);
		}
		i++;
	}
	box[i] = NULL;
	return (box);
}


char	**split_by_first_c(const char *str, char c)
{
	size_t	idx;
	char	**result;

	result = calloc(3, sizeof(char *));
	if (!result)
		return (NULL);
	idx = 0;
	while (true)
	{
		if (str[idx] == c || str[idx] == '\0')
		{
			result[0] = ft_substr(str, 0, idx);
			if (!result[0])
				return NULL;
			break ;
		}
		idx++;
	}
	if (str[idx])
	{
		result[1] = strdup(str + idx + 1);
		if (!result[1])
			return NULL;
	}
	return (result);
}