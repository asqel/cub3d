/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:29:31 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 18:05:53 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <mlx.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

void	display_fps(t_game *game, int64_t fps)
{
	int	px;

	if (fps < 0)
		fps = -fps;
	if (fps == 0)
		c3d_put_img(game, game->textures[TX_NUM_0],
			WIN_WIDTH - game->textures[TX_NUM_0].width, 0);
	else
	{
		px = WIN_WIDTH - game->textures[TX_NUM_0 + (fps % 10)].width;
		while (fps > 0)
		{
			c3d_put_img(game, game->textures[TX_NUM_0 + (fps % 10)], px, 0);
			fps /= 10;
			px -= game->textures[TX_NUM_0 + (fps % 10)].width;
		}
	}
}

int	test(void *param)
{
	struct timeval	start;
	struct timeval	stop;
	int64_t			elapsed;
	t_game			*ctx;

	ctx = param;
	gettimeofday(&start, NULL);
	c3d_tick(param);
	c3d_render(param);
	gettimeofday(&stop, NULL);
	elapsed = (stop.tv_sec - start.tv_sec) * 1000000
		+ stop.tv_usec - start.tv_usec;
	if (elapsed)
		display_fps(param, 1000 * 1000 / elapsed);
	else
		display_fps(param, 0x7FFFFFFFFFFFFFFFLL);
	mlx_put_image_to_window(ctx->mlx.mlx,
		ctx->mlx.win, ctx->mlx.backbuffer, 0, 0);
	return (0);
}

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->key_pressed[KEY_UP] = 1;
	else if (keycode == XK_a)
		game->key_pressed[KEY_LEFT] = 1;
	else if (keycode == XK_s)
		game->key_pressed[KEY_DOWN] = 1;
	else if (keycode == XK_d)
		game->key_pressed[KEY_RIGHT] = 1;
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		game->key_pressed[KEY_SPRINT] = 1;
	else if (keycode == XK_Left)
		game->key_pressed[KEY_LOOK_LEFT] = 1;
	else if (keycode == XK_Right)
		game->key_pressed[KEY_LOOK_RIGHT] = 1;
	else if (keycode == XK_Escape)
		c3d_exit(game, 0);
	return (0);
}

int	key_released(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->key_pressed[KEY_UP] = 0;
	else if (keycode == XK_a)
		game->key_pressed[KEY_LEFT] = 0;
	else if (keycode == XK_s)
		game->key_pressed[KEY_DOWN] = 0;
	else if (keycode == XK_d)
		game->key_pressed[KEY_RIGHT] = 0;
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		game->key_pressed[KEY_SPRINT] = 0;
	else if (keycode == XK_Left)
		game->key_pressed[KEY_LOOK_LEFT] = 0;
	else if (keycode == XK_Right)
		game->key_pressed[KEY_LOOK_RIGHT] = 0;
	return (0);
}

void prnt_map(char **map)
{
	int i;

	i = -1;
	while (map[++i])
		printf("%s\n", map[i]);
}

int	main(int argc, char **argv)
{
	static t_game	ctx;

	c3d_init(&ctx, argc, argv);
	ctx.buffer = (uint32_t *)mlx_get_data_addr(ctx.mlx.backbuffer,
			&argc, &argc, &argc);
	ctx.ceil_col = 0x0000FF;
	ctx.floor_col = 0x00ff00;
	ctx.map = (char *[]){"1111111", "1000011", "1111111"};
	mlx_hook(ctx.mlx.win, KeyPress, KeyPressMask, (void *)key_pressed, &ctx);
	mlx_hook(ctx.mlx.win, KeyRelease, KeyReleaseMask,
		(void *)key_released, &ctx);
	mlx_loop_hook(ctx.mlx.mlx, (void *)test, &ctx);
	mlx_loop(ctx.mlx.mlx);
}
