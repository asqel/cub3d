/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:24:49 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 17:58:17 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	launch_parsing(t_game *game, char *arg)
{
	game->map = read_map(arg);
	get_texture(game);
	printf("NO : %s\n", game->img_path[0]);
	clean_map(game);
	return(check_map(game));
}