/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:01:52 by iboukhss          #+#    #+#             */
/*   Updated: 2024/04/07 20:00:43 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "debug.h"
#include <unistd.h>
#include <string.h>

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	t_list			*node;
	size_t			len;
	char			*nl;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_lstfind(fd, &head);
	if (!node)
	{
		node = ft_lstnew(fd);
		ft_lstadd_back(&head, node);
	}
	PRINT_BUFFER(node->buf, BUFFER_SIZE + 1, "|");
	len = 0;
	line = NULL;
	while (1)
	{
		if (*node->rdp == '\0')
		{
			ft_bzero(node->buf, BUFFER_SIZE);
			if (read(fd, node->buf, BUFFER_SIZE) <= 0)
				return (line);
			node->rdp = node->buf;
		}
		PRINT_BUFFER(node->buf, BUFFER_SIZE + 1, "|");
		nl = strchr(node->rdp, '\n');
		if (nl)
		{
			line = ft_realloc(line, len, len + (nl - node->rdp + 2));
			len += nl - node->rdp + 1;
			strlcat(line, node->rdp, len + 1);
			node->rdp = nl + 1;
			return (line);
		}
		line = ft_realloc(line, len, len + strlen(node->rdp) + 1);
		len += strlen(node->rdp);
		strlcat(line, node->rdp, len + 1);
		node->rdp = node->buf + BUFFER_SIZE;
	}
}
