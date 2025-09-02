/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:57:58 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/02 18:41:09 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <fcntl.h>

char *rm_end_nl(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '\n')
			str[i] = 0;
	return (str);
}

static char	**read_map_fd(int fd)
{
	char	**map;
	int		i;

	i = 0;
	map = NULL;
	while (1)
	{
		map = ft_realloc(map, sizeof(char *) * (i + 1), 1);
		map[i] = rm_end_nl(get_next_line(fd));
		if (!map[i])
			break;
		i++;
	}
	return (map);
}
char **read_map(char *path)
{
	int	fd;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = read_map_fd(fd);
	return (map);
}