/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:24:49 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/03 14:36:12 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	launch_parsing(t_game *game, char *arg)
{
	game->map = read_map(arg);
	if (!game->map)
		return(c3d_set_err(ERR_PERROR, arg, NULL), 1);
	get_texture(game);
	clean_map(game);
	get_player(game);
	return(check_map(game));
}
