/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:01:51 by subaru            #+#    #+#             */
/*   Updated: 2022/12/05 01:09:18 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>

# define N_HASH_FUNC	5

typedef struct s_entry
{
	char		*key;
	char		*val;
	size_t		len;
	uint64_t	hash;
}	t_entry;

typedef struct s_dict
{
	t_entry		*ptr;
	size_t		len;
	size_t		cap;
}	t_dict;

typedef uint64_t	(*t_f_hash)(const unsigned char *s);

void		*ft_realloc(void *old_ptr, size_t old_size, size_t new_size);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);

uint64_t	hash_str(const char *s, int i);

t_dict		dict_new(size_t new_size);
void		*dict_delete(t_dict *dict);
bool		dict_insert(t_dict *dict, char *key, char *val);
t_entry		*dict_search(t_dict *dict, char *key);

#endif // DICT_H
