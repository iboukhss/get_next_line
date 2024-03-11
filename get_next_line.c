/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:58:40 by iboukhss          #+#    #+#             */
/*   Updated: 2024/03/09 14:09:17 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "get_next_line.h"
#include "stdio.h"

// global for testing
char	buf[BUFFER_SIZE] = { 0 };
size_t	total_bytes_read = 0;
size_t	bytes_consumed = 0;

char	*get_next_line(int fd)
{
	ssize_t bytes_read;
	size_t len;
	char *found;
	char *new;

	// if buffer has leftover bytes
	if (bytes_consumed < total_bytes_read)
	{
		found = memchr(buf, '\n', total_bytes_read - bytes_consumed);
		len = found - buf + 1;
		new = malloc(len + 1);
		memcpy(new, buf, len);
		new[len] = '\0';
		//memcpy(buf, found + 1, total_bytes_read - bytes_consumed - len);
		//buf[len] = '\0';
		bytes_consumed += len;
		return(new);
	}

	// else buffer should be empty
	bytes_read = read(fd, buf, sizeof(buf));
	if (bytes_read < 0)
	{
		return (NULL);
	}
	total_bytes_read += bytes_read;
	found = memchr(buf, '\n', bytes_read);
	len = found - buf + 1;
	new = malloc(len + 1);
	memcpy(new, buf, len);
	new[len] = '\0';
	memcpy(buf, found + 1, bytes_read - len);
	buf[bytes_read - len] = '\0';
	bytes_consumed += len;
	return(new);
}
