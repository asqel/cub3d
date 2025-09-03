/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:29:13 by axlleres          #+#    #+#             */
/*   Updated: 2025/09/03 14:37:12 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static char	**read_lines_fd(int fd)
{
	char	**map;
	int		len;
	char	**tmp;

	len = 0;
	map = NULL;
	while (1)
	{
		len++;
		tmp = ft_realloc(map, sizeof(char *) * (len + 1), 1);
		if (!tmp)
			return (free_split(map), c3d_set_err(ERR_PERROR, NULL, NULL), NULL);
		map = tmp;
		map[len - 1] = get_next_line(fd);
		if (!map[len - 1])
			return (free_split(map), c3d_set_err(ERR_PERROR, NULL, NULL), NULL);
		len++;
	}
	return (map);
}

static void	remove_endl(char **lines)
{
	int	i;
	int	k;

	i = -1;
	while (lines[++i])
	{
		k = ft_strlen(lines[i]) - 1;
		while (k >= 0 && lines[i][k] == '\n')
			lines[i][k--] = '\0';
	}
}

char	**read_lines(char *path)
{
	int		fd;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (c3d_set_err(ERR_PERROR, path, NULL), NULL);
	map = read_lines_fd(fd);
	if (map)
		remove_endl(map);
	return (map);
}
