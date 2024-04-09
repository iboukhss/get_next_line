/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:03:50 by iboukhss          #+#    #+#             */
/*   Updated: 2024/04/09 21:25:19 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "debug.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Find the node with the corresponding fildes */
t_list	*get_node_fd(t_list **head, int fd)
{
	t_list	*tmp;
	t_list	*node;

	tmp = *head;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	node = calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->rdp = node->buf;
	if (*head == NULL)
		*head = node;
	else
		tmp->next = node;
	return (node);
}

int	read_buffer(t_list *node)
{
	ssize_t	bytes_read;

	if (*node->rdp != '\0')
		return (1);
	bzero(node->buf, BUFFER_SIZE);
	bytes_read = read(node->fd, node->buf, BUFFER_SIZE);
	PRINT_BUFFER(node->buf, BUFFER_SIZE + 1, "|");
	if (bytes_read > 0)
	{
		node->rdp = node->buf;
		return (1);
	}
	return (0);
}

/* Not exactly following C standard implementation of realloc() */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	new = calloc(new_size, sizeof(char));
	if (!new)
		return (NULL);
	if (!ptr)
		return (new);
	memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}

char	*get_line(t_list *node)
{
	char	*nl;
	char	*line;
	size_t	len;
	size_t	buflen;

	len = 0;
	line = NULL;
	while (read_buffer(node))
	{
		nl = strchrnul(node->rdp, '\n');
		buflen = nl - node->rdp;
		if (*nl == '\n')
			++buflen;
		line = ft_realloc(line, len, len + buflen + 1);
		memcpy(line + len, node->rdp, buflen);
		node->rdp += buflen;
		len += buflen;
		if (*nl == '\n')
			break ;
	}
	return (line);
}
