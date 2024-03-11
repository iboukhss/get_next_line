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

// global for testing (zeroed)
char	buf[BUFFER_SIZE] = { 0 };

char	*get_next_line(int fd)
{
	ssize_t	bytes_read;
	size_t	line_len;
	char	*found;
	char	*new;

	// buffer is empty
	if (buf[0] == '\0')
	{
		bytes_read = read(fd, buf, sizeof(buf));
		if (bytes_read < 0)
		{
			return (NULL);
		}
		found = memchr(buf, '\n', bytes_read);
		while(found == NULL)
		{
			// do something
			return (NULL);
		}
		// found line in buffer
		line_len = found - buf + 1;
		new = malloc(line_len + 1);
		memcpy(new, buf, line_len);
		new[line_len] = '\0';
		// shift buffer to the left
		memmove(buf, found + 1, bytes_read - line_len);
		bzero(buf + bytes_read - line_len, line_len);
		return (new);
	}
	// buffer has leftover bytes
	found = memchr(buf, '\n', sizeof(buf));
	if (found == NULL)
	{
		found = memchr(buf, 0, sizeof(buf));
		if (found == NULL)
		{
			// problems
			return (NULL);
		}
	}
	bytes_read = read(fd, found, sizeof(buf) - (found - buf) + 1);
	found = memchr(found, '\n', bytes_read);
	line_len = found - buf + 1;
	new = malloc(line_len + 1);
	memcpy(new, buf, line_len);
	new[line_len] = '\0';
	memmove(buf, found + 1, bytes_read - line_len);
	bzero(buf + bytes_read - line_len, line_len);
	return (new);
}
