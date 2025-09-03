/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:21:14 by axlleres          #+#    #+#             */
/*   Updated: 2025/09/03 14:43:36 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_textures(t_game *ctx)
{
	int	i;

	i = -1;
	while (++i < TX_ENUM_MAX)
	{
		ft_free(ctx->textures[i].data);
		ctx->textures[i].data = NULL;
	}
}

void	free_mlx(t_game *ctx)
{
	if (ctx->mlx.backbuffer)
		mlx_destroy_image(ctx->mlx.mlx, ctx->mlx.backbuffer);
	if (ctx->mlx.win)
		mlx_destroy_window(ctx->mlx.mlx, ctx->mlx.win);
	if (ctx->mlx.mlx)
		mlx_destroy_display(ctx->mlx.mlx);
}

void	c3d_exit(t_game *ctx, int exit_code)
{
	static char *err_info;

	if (ctx == NULL)
		exit(exit_code);
	free_textures(ctx);
	free_mlx(ctx);
	c3d_set_err(1, NULL, &err_info);
	ft_free(err_info);
	exit(exit_code);
}
