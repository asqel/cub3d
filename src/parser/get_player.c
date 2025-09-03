/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:30:54 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/03 18:54:56 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	set_rot(t_game *game, char c)
{
	if (c == 'E')
		game->rot = M_PI / 180 * 0;
	else if (c == 'W')
		game->rot = M_PI / 180 * 180;
	else if (c== 'N')
		game->rot = M_PI / 180 * 270;
	else if (c == 'S')
		game->rot = M_PI / 180 * 90;
}

int	get_player(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (game->map[++x])
	{
		y = -1;
		while (game->map[x][++y])
		{
			if (ft_strchr("NEWS", game->map[x][y]) < 0)
				continue;
			set_rot(game, game->map[x][y]);
			game->p_x = y + 0.5;
			game->p_y = x + 0.5;
			game->map[x][y] = '0';
			return (1);
		}
	}
	return (0);
}
