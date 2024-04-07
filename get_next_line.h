/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:02:32 by iboukhss          #+#    #+#             */
/*   Updated: 2024/04/07 19:56:51 by iboukhss         ###   ########.fr       */
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

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *s, size_t old_size, size_t new_size);

t_list	*ft_lstnew(int fd);
void	ft_lstdelone(int fd, t_list **head);
void	ft_lstclear(t_list **head);
void	ft_lstadd_back(t_list **head, t_list *node);
t_list	*ft_lstfind(int fd, t_list **head);

#endif
