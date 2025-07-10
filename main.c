/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:29:31 by lucmansa          #+#    #+#             */
/*   Updated: 2025/07/10 00:56:28 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <mlx.h>

int	main(int argc, char **argv)
{
	t_mlx mlx;

	(void)argc;
	(void)argv;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	mlx_loop(mlx.mlx);
}