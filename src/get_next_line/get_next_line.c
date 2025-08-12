/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:10:07 by axlleres          #+#    #+#             */
/*   Updated: 2024/11/29 02:34:46 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*line;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_enough(fd, &rest) == -1)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	if (rest == NULL || *rest == '\0')
	{
		free(rest);
		return (rest = NULL, NULL);
	}
	len = ft_strchr(rest, '\n');
	if (len == -1)
		line = malloc(ft_strchr(rest, '\0') + 3);
	else
		line = malloc(len + 3);
	ft_strcpy_to_c(rest, line, '\n');
	str_shift_c(&rest, '\n');
	return (line);
}
