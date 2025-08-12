/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:29:31 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 17:15:35 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <mlx.h>

void prnt_map(char **map)
{
	int i;

	i = -1;
	while (map[++i])
		printf("%s\n", map[i]);
}

int	main(int argc, char **argv)
{

	t_game game;

	(void)argc;
	game.img_path[0] = 0;
	game.img_path[1] = 0;
	game.img_path[2] = 0;
	game.img_path[3] = 0;
	game.cell = 0;
	game.flor = 0;
	if (launch_parsing(&game, argv[1]))
		return (1);
	return (0);
}