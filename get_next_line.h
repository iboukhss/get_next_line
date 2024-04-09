/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:02:32 by iboukhss          #+#    #+#             */
/*   Updated: 2024/04/09 20:02:43 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>

typedef struct s_list
{
	int				fd;
	char			buf[BUFFER_SIZE + 1];
	char			*rdp;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*get_node_fd(t_list **head, int fd);
int		read_buffer(t_list *node);
char	*get_line(t_list *node);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif
