/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:52:15 by axlleres          #+#    #+#             */
/*   Updated: 2024/11/29 02:35:50 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

int		ft_strchr(char *s, int c);
void	ft_strcpy_to_c(const char *src, char *dest, char c);
void	str_append_to_c(char **str, char *append, char c);
int		read_enough(int fd, char **rest);
void	str_shift_c(char **str, char c);

char	*get_next_line(int fd);

#endif