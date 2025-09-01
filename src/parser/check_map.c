/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:58:21 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 14:26:06 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
					return (0);
		}
	}
	return (1);
}

int	check_map(t_game *game)
{
	if (!game->tx_path[0] || !game->tx_path[1] || !game->tx_path[2] || !game->tx_path[3] || !game->cell || !game->flor)
		return (printf("Mising texture\n"), 1);
	if (!check_wall(game->map))
		return (printf("Mising wall\n"), 1);
	return (0);
}