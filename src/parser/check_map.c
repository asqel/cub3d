/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:58:21 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/03 18:43:18 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_pos(char **map, int x, int y)
{
	if (x == 0)
		return 1;
	if (map[y][x + 1] == '\0')
		return 1;
	if (y == 0)
		return 1;
	if (map[y + 1] == NULL)
		return 1;
	if ((map[y][x + 1] != '1' && map[y][x + 1] != '0') || (map[y][x - 1] != '1' && map[y][x - 1] != '0'))
		return 1;
	return ((map[y + 1][x] != '1' && map[y + 1][x] != '0') || (map[y - 1][x] != '1' && map[y - 1][x] != '0'));
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
			if (map[i][j] == '0' && check_pos(map, j, i))
				return (0);
		}
	}
	return (1);
}

int	check_char(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
			if (ft_strchr("01 ", game->map[y][x]) < 0)
				return (1);
	}
	return (0);
}

int	check_map(t_game *game)
{
	if (!game->tx_path[0] || !game->tx_path[1] || !game->tx_path[2] || !game->tx_path[3])
		return (c3d_set_err(ERR_TEXTURE, NULL, NULL), 1);
	if (game->ceil_col == 0xFF000000 || game->floor_col == 0xFF000000)
		return (c3d_set_err(ERR_COLOR, NULL, NULL), 1);
	if (!check_wall(game->map))
		return (c3d_set_err(ERR_WALL, NULL, NULL), 1);
	if (check_char(game))
		return (c3d_set_err(ERR_CHAR, NULL, NULL), 1);
	return (0);
}
