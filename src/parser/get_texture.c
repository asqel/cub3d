/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:21 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 14:25:59 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void free_tab(char **tab)
{
	int i;

	i = -1;
	while(tab[++i])
		free(tab[i]);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}


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

void	get_texture(t_game *game)
{
	int i;

	i = 0;
	while ((!game->tx_path[0] || !game->tx_path[1] || !game->tx_path[2]
		|| !game->tx_path[3] || !game->cell || !game->flor) && game->map[i])
	{
		if (game->map[i][0] == 'N' && game->map[i][1] == 'O' && game->map[i][2] == ' ')
			game->tx_path[0] = get_str(game->map[i], 2);
		else if (game->map[i][0] == 'S' && game->map[i][1] == 'O' && game->map[i][2] == ' ')
			game->tx_path[1] = get_str(game->map[i], 2);
		else if (game->map[i][0] == 'W' && game->map[i][1] == 'E' && game->map[i][2] == ' ')
			game->tx_path[2] = get_str(game->map[i], 2);
		else if (game->map[i][0] == 'E' && game->map[i][1] == 'A' && game->map[i][2] == ' ')
			game->tx_path[3] = get_str(game->map[i], 2);
		else if (game->map[i][0] == 'F' && game->map[i][1] == ' ')
			game->flor = get_str(game->map[i], 1);
		else if (game->map[i][0] == 'C' && game->map[i][1] == ' ')
			game->cell = get_str(game->map[i], 1);
		i++;
	}
}
