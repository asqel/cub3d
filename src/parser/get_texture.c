/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:21 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 16:52:48 by lucmansa         ###   ########.fr       */
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

void	remove_line(char ***map, int i)
{
	while((*map)[i + 1])
	{
		(*map)[i] = (*map)[i + 1];
		i++;
	}
	(*map)[i] = NULL;
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

char **get_texture(t_game *game, char **map)
{
	int i;

	i = 0;
	while ((!game->img_path[0] || !game->img_path[1] || !game->img_path[2] || !game->img_path[3] || !game->cell || !game->flor) && map[i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
			game->img_path[0] = get_str(map[i], 2);
		else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
			game->img_path[1] = get_str(map[i], 2);
		else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
			game->img_path[2] = get_str(map[i], 2);
		else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
			game->img_path[3] = get_str(map[i], 2);
		else if (map[i][0] == 'F' && map[i][1] == ' ')
			game->flor = get_str(map[i], 1);
		else if (map[i][0] == 'c' && map[i][1] == ' ')
			game->cell = get_str(map[i], 1);
		else
		{
			i++;
			continue;
		}
		remove_line(&map, i);
	}
	return (map);
}

