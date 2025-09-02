/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:10:07 by axlleres          #+#    #+#             */
/*   Updated: 2025/09/02 18:12:08 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
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
		ft_free(rest);
		rest = NULL;
		return (NULL);
	}
	if (rest == NULL || *rest == '\0')
	{
		ft_free(rest);
		return (rest = NULL, NULL);
	}
	len = ft_strchr(rest, '\n');
	if (len == -1)
		line = ft_malloc(ft_strchr(rest, '\0') + 3);
	else
		line = ft_malloc(len + 3);
	ft_strcpy_to_c(rest, line, '\n');
	str_shift_c(&rest, '\n');
	return (line);
}
