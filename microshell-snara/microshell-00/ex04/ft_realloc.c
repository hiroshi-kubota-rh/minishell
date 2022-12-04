/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:13:39 by subaru            #+#    #+#             */
/*   Updated: 2022/07/01 20:04:56 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;

	i = count * size + !(count && size);
	if (size && i / size != count)
	{
		errno = ENOMEM;
		return (NULL);
	}
	p = malloc(i);
	if (!p)
		return (NULL);
	while (0 < i--)
		p[i] = '\0';
	return ((void *)p);
}

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	unsigned char *const	new_ptr = ft_calloc(1, new_size);
	size_t					i;

	if (new_ptr)
	{
		i = 0;
		while (i < old_size && i < new_size)
		{
			new_ptr[i] = ((unsigned char *)old_ptr)[i];
			++i;
		}
		free(old_ptr);
	}
	return (new_ptr);
}
