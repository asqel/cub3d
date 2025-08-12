/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:29:31 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 16:29:28 by lucmansa         ###   ########.fr       */
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
	char **map;
	t_game game;

	(void)argc;
	game.img_path[0] = 0;
	game.img_path[1] = 0;
	game.img_path[2] = 0;
	game.img_path[3] = 0;
	game.cell = 0;
	game.flor = 0;
	map = read_map(argv[1]);
	prnt_map(map);
	map = get_texture(&game, map);
	printf("-----------\n");
	printf("NO path : %s\n", game.img_path[0]);
	printf("SO path : %s\n", game.img_path[1]);
	printf("-----------\n");
	prnt_map(map);
		
}