/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:58:21 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 17:16:12 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_map(t_game *game)
{
	if (!game->img_path[0] || !game->img_path[1] || !game->img_path[2] || !game->img_path[3] || !game->cell || !game->flor)
		return (printf("Mising texture\n"), 1);
	return (0);
}