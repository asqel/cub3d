/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:24:49 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 16:37:33 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	launch_parsing(t_game *game, char *arg)
{
	game->map = read_map(arg);
	get_texture(game);
	clean_map(game);
	get_player(game);
	return(check_map(game));
}