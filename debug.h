/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <iboukhss@student.42luxe...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:46:49 by iboukhss          #+#    #+#             */
/*   Updated: 2024/04/07 18:00:40 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include <stdio.h>

# ifdef DEBUG
#  define PRINT_BUFFER(buf, size, sep) do { \
		printf("%08d: %s", size, sep); \
		for (int x = 0; x < size; ++x) \
		{ \
			if (buf[x] == '\n') \
				printf("$"); \
			else if (buf[x] < ' ' || buf[x] > '~') \
				printf("."); \
			else \
				printf("%c", buf[x]); \
		} \
		printf("%s\n", sep); \
	} while (0)
# else
#  define PRINT_BUFFER(buf, size, sep)
# endif

#endif
