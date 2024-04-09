/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:01:52 by iboukhss          #+#    #+#             */
/*   Updated: 2024/04/09 19:17:12 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "debug.h"

/*
 * Total functions used so far: 9/10
 *
 * 1 - get_next_line()
 * 2 - get_node_fd()
 * 3 - read_buffer()
 * 4 - get_line()
 * 5 - bzero()
 * 6 - calloc()
 * 7 - memcpy()
 * 8 - strchrnul()
 * 9 - realloc()
 */

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	t_list			*node;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node_fd(&head, fd);
	if (!node)
		return (NULL);
	PRINT_BUFFER(node->buf, BUFFER_SIZE + 1, "|");
	return (get_line(node));
}
