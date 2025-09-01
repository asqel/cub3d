/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:58:21 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 16:24:31 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_size(char **map, char c)
{
	int i;

	i = 0;
	if (c == 'h')
	{
		while (map[i])
			i++;
		return (i);
	}
		i = 0;
	if (c == 'w')
	{
		while (map[3][i])
			i++;
		return (i);
	}
	return (0);
}

int	check_wall(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
				if ((map[i + 1][j] != '1' || map[i + 1][j] != '0') && (map[i - 1][j] != '1' || map[i - 1][j] != '0') && (map[i][j + 1] != '1' || map[i][j + 1] != '0') && (map[i][j - 1] != '1' || map[i][j - 1] != '0'))
					return (1);
		}
	}
	return (1);
}

int	check_map(t_game *game)
{
	if (!game->tx_path[0] || !game->tx_path[1] || !game->tx_path[2] || !game->tx_path[3] || !game->ceil_col || !game->floor_col)
		return (printf("Mising texture\n"), 1);
	if (!check_wall(game->map))
		return (printf("Mising wall\n"), 1);
	game->map_height = get_size(game->map, 'h');
	game->map_width = get_size(game->map, 'w');
	return (0);
}