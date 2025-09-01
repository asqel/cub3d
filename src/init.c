/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:41:15 by axlleres          #+#    #+#             */
/*   Updated: 2025/09/01 16:40:24 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	c3d_load_textures(t_game *ctx)
{
	static char	path[] = "assets/0.xpm";
	int			i;

	c3d_load_texture(ctx->mlx.mlx, ctx->tx_path[0],
		&ctx->textures[DIR_NORTH]);
	c3d_load_texture(ctx->mlx.mlx, ctx->tx_path[1],
		&ctx->textures[DIR_EAST]);
	c3d_load_texture(ctx->mlx.mlx, ctx->tx_path[2],
		&ctx->textures[DIR_SOUTH]);
	c3d_load_texture(ctx->mlx.mlx, ctx->tx_path[3],
		&ctx->textures[DIR_WEST]);
	i = -1;
	while (++i < 10)
	{
		path[7] = '0' + i;
		c3d_load_texture(ctx->mlx.mlx, path, &ctx->textures[TX_NUM_0 + i]);
	}
}

void	c3d_init(t_game *ctx, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ctx->mlx.mlx = mlx_init();
	ctx->mlx.win = mlx_new_window(ctx->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	ctx->mlx.backbuffer = mlx_new_image(ctx->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	c3d_load_textures(ctx);
}
