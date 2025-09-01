/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:30:54 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 16:30:25 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int get_player(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (game->map[++x])
	{
		y = -1;
		while (game->map[x][++y])
		{
			if (game->map[x][y] == 'N' || game->map[x][y] == 'E' || game->map[x][y] == 'S' || game->map[x][y] == 'W')
			{
				if (game->map[x][y] == 'N')
					game->rot = 0;
				if (game->map[x][y] == 'S')
					game->rot = 180;
				if (game->map[x][y] == 'E')
					game->rot = 90;
				if (game->map[x][y] == 'W')
					game->rot = 270;
				game->p_x = x;
				game->p_y = y;
				game->map[x][y] = '0';
				return (1);
			}
		}
	}
	return (0);
}
