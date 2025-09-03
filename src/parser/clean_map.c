/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:27:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/03 15:55:28 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_map_size(t_game *game)
{
	int x;
	int	y;

	y = -1;
	while (game->map[++y])
	{
		x = 0;
		while (game->map[y][x])
			x++;
		if (x > game->map_width)
			game->map_width = x;
	}
	game->map_height = y;
}

void	remove_line(char ***map, int i)
{
	while((*map)[i + 1])
	{
		(*map)[i] = (*map)[i + 1];
		i++;
	}
	(*map)[i] = NULL;
}

void	resize_map(t_game *game)
{
	int	i;
	int	k;

	i = -1;
	while (++i < game->map_height)
		if (ft_strlen(game->map[i]) < game->map_width)
		{
			game->map[i] = ft_realloc(game->map[i], sizeof(char) * game->map_width + 1, 1);
			k = ft_strlen(game->map[i]);
			while (k < game->map_width)
				game->map[i][k++] = ' ';
		}
}

void	clean_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if ((game->map[i][0] == 'N' && game->map[i][1] == 'O' && game->map[i][2] == ' ')
		|| (game->map[i][0] == 'S' && game->map[i][1] == 'O' && game->map[i][2] == ' ')
		|| (game->map[i][0] == 'W' && game->map[i][1] == 'E' && game->map[i][2] == ' ')
		|| (game->map[i][0] == 'E' && game->map[i][1] == 'A' && game->map[i][2] == ' ')
		|| (game->map[i][0] == 'F' && game->map[i][1] == ' ')
		|| (game->map[i][0] == 'C' && game->map[i][1] == ' '))
		{
			ft_free(game->map[i]);
			remove_line(&game->map, i);
		}
		else
			i++;
	}
	get_map_size(game);
	resize_map(game);
}
