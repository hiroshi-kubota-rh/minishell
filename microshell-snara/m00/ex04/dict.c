/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:59:03 by subaru            #+#    #+#             */
/*   Updated: 2022/12/05 01:13:54 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "hotrace.h"
#include "dict.h"

t_dict	dict_new(size_t new_size)
{
	t_dict	dict;

	dict = (t_dict){};
	dict.ptr = ft_realloc(NULL, 0, sizeof(t_entry) * new_size);
	if (dict.ptr)
		dict.cap = new_size;
	return (dict);
}

void	*dict_delete(t_dict *dict)
{
	size_t	i;
	t_entry	entry;

	i = 0;
	while (i < dict->cap)
	{
		entry = dict->ptr[i];
		free(entry.key);
		free(entry.val);
		dict->ptr[i] = (t_entry){};
		++i;
	}
	free(dict->ptr);
	*dict = (t_dict){};
	return (NULL);
}

bool	dict_expand(t_dict *dict)
{
	if (!dict->ptr || dict->len >= dict->cap / 4)
	{
		dict->ptr = ft_realloc(dict->ptr, sizeof(t_entry) * dict->cap,
				sizeof(t_entry) * (dict->cap * 4 + !dict->cap * 16));
		if (!dict->ptr)
		{
			*dict = (t_dict){};
			return (false);
		}
		dict->cap = dict->cap * 4 + !dict->cap * 16;
	}
	return (true);
}

bool	dict_insert(t_dict *dict, char *key, char *val)
{
	int		i;
	t_entry	entry;
	t_entry	*found;

	i = 0;
	entry = (t_entry){key, val, ft_strlen(key), 0};
	if (!dict_expand(dict))
		return (false);
	while (1)
	{
		if (i >= N_HASH_FUNC)
			return (false);
		entry.hash = hash_str(key, i++);
		found = &dict->ptr[entry.hash % dict->cap];
		if (!found->key || !ft_strcmp(key, found->key))
			break ;
	}
	free(found->key);
	free(found->val);
	*found = entry;
	dict->len += 1;
	return (true);
}

t_entry	*dict_search(t_dict *dict, char *key)
{
	int		i;
	t_entry	entry;
	t_entry	*found;

	i = 0;
	entry = (t_entry){key, NULL, ft_strlen(key), 0};
	while (i < N_HASH_FUNC)
	{
		entry.hash = hash_str(key, i++);
		found = &dict->ptr[entry.hash % dict->cap];
		if (found->key && !ft_strcmp(key, found->key))
			return (found);
	}
	return (NULL);
}
