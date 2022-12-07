/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:41:16 by subaru            #+#    #+#             */
/*   Updated: 2022/04/03 21:16:36 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "dict.h"

uint64_t	hash_fnv1(const unsigned char *s);
uint64_t	hash_fnv1a(const unsigned char *s);
uint64_t	hash_origin(const unsigned char *s);
uint64_t	hash_djb2(const unsigned char *s);
uint64_t	hash_jenkins(const unsigned char *s);

uint64_t	hash_str(const char *s, int i)
{
	const t_f_hash	f_hash[N_HASH_FUNC] = {
		hash_fnv1, hash_fnv1a, hash_origin, hash_jenkins, hash_djb2};

	if (!s || !s[0] || i < 0 || N_HASH_FUNC <= i)
		return (0);
	return (f_hash[i]((unsigned char *)s));
}
