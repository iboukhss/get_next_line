/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:35:37 by iboukhss          #+#    #+#             */
/*   Updated: 2024/05/13 22:04:31 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"

static t_list	*get_node_fd(t_list **head, int fd)
{
	t_list	*lst;
	t_list	*node;

	lst = *head;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->rdp = node->buf;
	if (*head == NULL)
		*head = node;
	else
		lst->next = node;
	return (node);
}

static int	read_buffer(t_list *node)
{
	ssize_t	bytes_read;

	if (*node->rdp)
		return (1);
	node->rdp = node->buf;
	ft_memset(node->buf, 0, BUFFER_SIZE);
	bytes_read = read(node->fd, node->buf, BUFFER_SIZE);
	if (bytes_read > 0)
		return (1);
	return (0);
}

static char	*get_line(t_list *node)
{
	char	*line;
	size_t	len;
	char	*delim;
	size_t	offset;

	len = 0;
	line = NULL;
	while (read_buffer(node))
	{
		delim = ft_strchrnul(node->rdp, '\n');
		offset = delim - node->rdp;
		if (*delim == '\n')
			++offset;
		line = ft_realloc(line, len, len + offset + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line + len, node->rdp, offset);
		len += offset;
		line[len] = '\0';
		node->rdp += offset;
		if (*delim == '\n')
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	t_list			*node;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node_fd(&head, fd);
	if (!node)
		return (NULL);
	next_line = get_line(node);
	return (next_line);
}
