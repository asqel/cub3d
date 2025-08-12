/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:24:49 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 16:54:05 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <fcntl.h>

static char	**read_map_fd(int fd)
{
	char	**map;
	int		i;

	i = 0;
	map = NULL;
	while (1)
	{
		map = ft_realloc(map, sizeof(char *) * (i + 1), 1);
		map[i] = ft_strdup(get_next_line(fd));
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
		return (c3d_set_err(1), NULL);
	map = read_map_fd(fd);
	return (map);
}