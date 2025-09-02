#include "cube3d.h"

int	tick_hook(void *param)
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
