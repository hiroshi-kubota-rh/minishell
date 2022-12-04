/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:41:16 by subaru            #+#    #+#             */
/*   Updated: 2022/04/03 19:47:44 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint64_t	hash_origin(const unsigned char *s)
{
	uint64_t	hash1;
	uint64_t	hash2;
	uint64_t	c;

	if (!s || !s[0])
		return (0);
	hash1 = 5381;
	hash2 = hash1;
	while (*s != 0)
	{
		c = s[0];
		hash1 = ((hash1 << 5) + hash1) ^ c;
		c = s[1];
		if (c == '\0')
			break ;
		hash2 = ((hash2 << 5) + hash2) ^ c;
		s += 2;
	}
	return ((hash1 + (hash2 * 1566083941)));
}

// http://www.cse.yorku.ca/~oz/hash.html
uint64_t	hash_djb2(const unsigned char *s)
{
	uint64_t	hash;

	if (!s || !s[0])
		return (0);
	hash = 5381;
	while (*s)
	{
		hash = ((hash << 5) + hash) + *s;
		s++;
	}
	return (hash);
}

uint64_t	hash_jenkins(const unsigned char *s)
{
	uint64_t	hash;

	if (!s || !s[0])
		return (0);
	hash = 0;
	while (*s)
	{
		hash += *s;
		hash += (hash << 10);
		hash ^= (hash >> 6);
		s++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash);
}

uint64_t	hash_fnv1(const unsigned char *s)
{
	uint64_t	hash;

	if (!s || !s[0])
		return (0);
	hash = 2166136261;
	while (*s)
	{
		hash *= 16777619;
		hash ^= *s;
		s++;
	}
	return (hash);
}

uint64_t	hash_fnv1a(const unsigned char *s)
{
	uint64_t	hash;

	if (!s || !s[0])
		return (0);
	hash = 2166136261;
	while (*s)
	{
		hash ^= *s;
		hash *= 16777619;
		s++;
	}
	return (hash);
}
