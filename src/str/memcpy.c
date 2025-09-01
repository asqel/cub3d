/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:24:49 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 13:54:10 by axlleres         ###   ########.fr       */
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

void	ft_memcpy(char *dest, const char *src, int len)
{
	while (len-- > 0)
		dest[len] = src[len];
}
