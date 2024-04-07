/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:03:50 by iboukhss          #+#    #+#             */
/*   Updated: 2024/04/07 19:57:25 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr = '\0';
		++ptr;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	*ft_realloc(void *s, size_t old_size, size_t new_size)
{
	void	*ptr;

	if (!new_size)
	{
		free(s);
		return (NULL);
	}
	ptr = calloc(1, new_size);
	if (!ptr)
		return (NULL);
	if (!s)
		return (ptr);
	memcpy(ptr, s, old_size);
	free(s);
	return (ptr);
}

t_list	*ft_lstnew(int fd)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->rdp = new->buf;
	return (new);
}

void	ft_lstdelone(int fd, t_list **head)
{
	t_list	*curr;
	t_list	*prev;

	if (fd < 0 || !head)
		return ;
	if (!*head)
		return ;
	curr = *head;
	prev = NULL;
	while (curr && curr->fd != fd)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (!prev)
		*head = curr->next;
	else
		prev->next = curr->next;
	free(curr);
}

void	ft_lstclear(t_list **head)
{
	if (!head)
		return ;
	while (*head)
		ft_lstdelone((*head)->fd, head);
}

void	ft_lstadd_back(t_list **head, t_list *node)
{
	t_list	*tail;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tail = *head;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
}

t_list	*ft_lstfind(int fd, t_list **head)
{
	t_list	*find;

	if (fd < 0 || !head)
		return (NULL);
	if (!*head)
		return (NULL);
	find = *head;
	while (find && find->fd != fd)
		find = find->next;
	return (find);
}
