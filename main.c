/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: axlleres <axlleres@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/07/09 15:29:31 by lucmansa		  #+#	#+#			 */
/*   Updated: 2025/08/29 19:24:34 by axlleres         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "cube3d.h"
#include <mlx.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>


void put_img(t_game *game, t_img img, int x, int y, uint32_t *buffer) {
	(void)game;
	for (int i = 0; i < img.width; i++) {
		uint32_t *column = &img.data[i * img.height];
		for (int k = 0; k < img.height; k++) {
			if (column[k] >> 24 == 0)
				buffer[(i + x) + (k + y) * WIN_WIDTH] = column[k];
		}
	}
}

int test(void *param) {
	struct timeval start, stop;
	gettimeofday(&start, NULL);
	t_game *game = (t_game *)param;

	if (game->key_pressed[1])
		game->rot += M_PI / 180 * 1;
	else if (game->key_pressed[3])
		game->rot -= M_PI / 180 * 1;
	if (game->key_pressed[0]) {
		game->p_x += cos(game->rot) * 0.04 * (game->key_pressed[10] ? 2 : 1);
		game->p_y += sin(game->rot) * 0.04 * (game->key_pressed[10] ? 2 : 1);
	}
	if (game->key_pressed[2]) {
		game->p_x -= cos(game->rot) * 0.04 * (game->key_pressed[10] ? 2 : 1);
		game->p_y -= sin(game->rot) * 0.04 * (game->key_pressed[10] ? 2 : 1);
	}
	c3d_render(game);
	gettimeofday(&stop, NULL);
	long seconds = stop.tv_sec - start.tv_sec;
	long micros = stop.tv_usec - start.tv_usec;
	long elapsed = seconds * 1000 + micros / 1000;
	int fps;
	if (elapsed)
		fps = 1000 / elapsed;
	else
		fps = 0x7FFFFFFF;
	if (fps == 0) {
		int px = WIN_WIDTH - game->numberes[0].width;
		int py = 0;
		put_img(game, game->numberes[0], px, py, game->buffer);
	}
	else {
		int px = WIN_WIDTH - game->numberes[fps % 10].width;
		int py = 0;
		while (fps > 0) {
			put_img(game, game->numberes[fps % 10], px, py, game->buffer);
			fps /= 10;
			px -= game->numberes[fps % 10].width;
		}
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.backbuffer, 0, 0);
	return (0);
}

int key_pressed(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->key_pressed[0] = 1; // w
	else if (keycode == XK_a)
		game->key_pressed[1] = 1; // a
	else if (keycode == XK_s)
		game->key_pressed[2] = 1; // s
	else if (keycode == XK_d)
		game->key_pressed[3] = 1; // d
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		game->key_pressed[10] = 1;
	else if (keycode == XK_space)
		printf("player (%f %f) rot %f\n", game->p_x, game->p_y, game->rot);
	else if (keycode == XK_r)
		game->rot = 0;
	return 0;
}

int key_released(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->key_pressed[0] = 0; // w
	else if (keycode == XK_a)
		game->key_pressed[1] = 0; // a
	else if (keycode == XK_s)
		game->key_pressed[2] = 0; // s
	else if (keycode == XK_d)
		game->key_pressed[3] = 0; // d
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		game->key_pressed[10] = 0;
	return 0;
}

int	main(int argc, char **argv)
{
	t_mlx mlx;
	t_game game;

	(void)argc;
	(void)argv;
	game = (t_game){0};
	c3d_init(&game, argc, argv);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	mlx.backbuffer = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	game = (t_game){0};
	game.mlx = mlx;
	game.p_x = 1.5;
	game.p_y = 1.5;
	game.rot = 0;
	game.map = (char *[]){
		"111111111111111111111111",
		"100000000001000000000001",
		"111111111111111111111111",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"111111111111111111111111"
	};
	game.map_height = 16;
	game.map_width  = 24;
	c3d_load_texture(mlx.mlx, "assets/grass.xpm", &game.textures[DIR_NORTH]);
	c3d_load_texture(mlx.mlx, "assets/dragon.xpm", &game.textures[DIR_EAST]);
	c3d_load_texture(mlx.mlx, "assets/grass.xpm", &game.textures[DIR_SOUTH]);
	c3d_load_texture(mlx.mlx, "assets/dragon.xpm", &game.textures[DIR_WEST]);
	char path[] = "assets/0.xpm";
	for (int i = 0; i < 10; i++) {
		path[7] = '0' + i;
		c3d_load_texture(mlx.mlx, path, &game.numberes[i]);
	}
	game.buffer = (uint32_t *)mlx_get_data_addr(game.mlx.backbuffer, &argc, &argc, &argc);
	game.ceil_col = 0x0000FF;
	game.floor_col = 0x00ff00;

	mlx_mouse_hide(mlx.mlx, mlx.win);

	mlx_hook(mlx.win, KeyPress, KeyPressMask, (void *)key_pressed, &game);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, (void *)key_released, &game);
	mlx_loop_hook(mlx.mlx, (void *)test, &game);
	mlx_loop(mlx.mlx);
}