/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:27:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 18:15:00 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	remove_line(char ***map, int i)
{
	while((*map)[i + 1])
	{
		(*map)[i] = (*map)[i + 1];
		i++;
	}
	(*map)[i] = NULL;
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
			remove_line(&game->map, i);
		else
			i++;
	}
}
