/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:21 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/03 18:46:48 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*get_str(char *seg, int i)
{
	char	*res;
	int		size;

	skip_spaces(seg, &i);
	if (!seg[i])
		return (NULL);
	size = 0;
	while (seg[i + size])
	{
		if (ft_is_space(seg[i + size]))
			break ;
		size++;
	}
	res = ft_substr(seg, i, size);
	return (res);
}

static int	set_texture(t_game *game, int i)
{
	if (!ft_strncmp(game->map[i], "NO ", 3))
	{
		if (game->tx_path[DIR_NORTH])
			return (1);
		game->tx_path[DIR_NORTH] = get_str(game->map[i], 2);
	}
	else if (!ft_strncmp(game->map[i], "SO ", 3))
	{
		if (game->tx_path[DIR_SOUTH])
			return (1);
		game->tx_path[DIR_SOUTH] = get_str(game->map[i], 2);
	}
	else if (!ft_strncmp(game->map[i], "WE ", 3))
	{
		if (game->tx_path[DIR_WEST])
			return (1);
		game->tx_path[DIR_WEST] = get_str(game->map[i], 2);
	}
	else if (!ft_strncmp(game->map[i], "EA ", 3))
	{
		if (game->tx_path[DIR_EAST])
			return (1);
		game->tx_path[DIR_EAST] = get_str(game->map[i], 2);
	}
	else if (!ft_strncmp(game->map[i], "F ", 2))
	{
		if (game->floor_col != 0xFF000000)
			return (1);
		game->floor_col = get_color(&game->map[i][1]);
	}
	else if (!ft_strncmp(game->map[i], "C ", 2))
	{
		if (game->ceil_col != 0xFF000000)
			return (1);
		game->ceil_col = get_color(&game->map[i][1]);
	}
	return (0);		
}

int	get_texture(t_game *game)
{
	int i;

	i = 0;
	while (!ft_strncmp(game->map[i], "NO ", 3) || !ft_strncmp(game->map[i], "SO ", 3)
			|| !ft_strncmp(game->map[i], "WE ", 3) || !ft_strncmp(game->map[i], "EA ", 3)
			|| !ft_strncmp(game->map[i], "F ", 2) || !ft_strncmp(game->map[i], "C ", 2))
	{
		if (set_texture(game, i))
			return (1);
		i++;
	}
	return (0);
}
