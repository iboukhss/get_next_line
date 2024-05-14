/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:35:22 by iboukhss          #+#    #+#             */
/*   Updated: 2024/05/13 22:04:48 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr = (unsigned char)c;
		++ptr;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	dp = dest;
	sp = src;
	while (n--)
	{
		*dp = *sp;
		++dp;
		++sp;
	}
	return (dest);
}

/**
 * Excerpt from realloc(3) manual page
 * 
 * Portable programs should not use private memory allocators,
 * as POSIX and the C standard do not allow replacement of malloc(),
 * free(), calloc(), and realloc().
 */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	unsigned char	*new;

	new = malloc(new_size * sizeof(*new));
	if (!new)
		return (NULL);
	if (!ptr)
		return (new);
	ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}

char	*ft_strchrnul(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		++s;
	}
	return ((char *)s);
}
