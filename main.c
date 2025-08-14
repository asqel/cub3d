/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:29:31 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/14 13:33:27 by axlleres         ###   ########.fr       */
/*                                                                            */
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
	t_ray rays[WIN_WIDTH];

	if (game->key_pressed[1])
		game->rot += M_PI / 180 * 1;
	else if (game->key_pressed[3])
		game->rot -= M_PI / 180 * 1;
	if (game->key_pressed[0]) {
		game->player_x += cos(game->rot) * 0.04 * (game->key_pressed[10] ? 2 : 1);
		game->player_y += sin(game->rot) * 0.04 * (game->key_pressed[10] ? 2 : 1);
	}
	if (game->key_pressed[2]) {
		game->player_x -= cos(game->rot) * 0.04 * (game->key_pressed[10] ? 2 : 1);
		game->player_y -= sin(game->rot) * 0.04 * (game->key_pressed[10] ? 2 : 1);
	}

	get_ray(game, rays, (int)game->player_x, (int)game->player_y);
	int tmp;
	uint32_t *buffer = (uint32_t *)mlx_get_data_addr(game->mlx.backbuffer, &tmp, &tmp, &tmp);
	//printf("RAYS\n");
	for (int i = 0; i < WIN_WIDTH; i++) {
		if (rays[i].face_hit == -1) {
			for (int y = 0; y < WIN_HEIGHT / 2; y++)
				buffer[y * WIN_WIDTH + i] = 0xFF0000;
			for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
				buffer[y * WIN_WIDTH + i] = 0x0000FF;
			continue;
		}
		//printf("Ray %d: x=%.2f, y=%.2f, dist=%.2f, face_hit=%d\n", i, rays[i].x, rays[i].y, rays[i].dist, rays[i].face_hit);
		//rays[i].dist = rays[i].dist * cos((i - WIN_WIDTH / 2) * FOV / WIN_WIDTH * M_PI / 180);
		int line_height = ((int)(WIN_HEIGHT / (rays[i].dist)));
		int y_start = (WIN_HEIGHT - line_height) / 2;
		int y_end = y_start + line_height;
		uint32_t *texture_column;
		int tex_height;
		if (rays[i].face_hit == DIR_NORTH) {
			texture_column = &game->textures[0].data[((int)(game->textures[0].width * rays[i].texture_percent) * game->textures[0].height)];
			tex_height = game->textures[0].height;
		}
		else if (rays[i].face_hit == DIR_EAST) {
			texture_column = &game->textures[1].data[((int)(game->textures[1].width * rays[i].texture_percent) * game->textures[1].height)];
			tex_height = game->textures[1].height;
		}
		else if (rays[i].face_hit == DIR_SOUTH) {
			texture_column = &game->textures[2].data[((int)(game->textures[2].width * rays[i].texture_percent) * game->textures[2].height)];
			tex_height = game->textures[2].height;
		}
		else {
			texture_column = &game->textures[3].data[((int)(game->textures[3].width * rays[i].texture_percent) * game->textures[3].height)];
			tex_height = game->textures[3].height;
		}
		int y = y_start;
		if (y < 0)
			y = 0;
		if (y >= WIN_HEIGHT)
			y = WIN_HEIGHT;
		if (y_end > WIN_HEIGHT)
			y_end = WIN_HEIGHT;
		if (y_end < 0)
			y_end = 0;
		for (; y < y_end; y++) {
			buffer[y * WIN_WIDTH + i] = texture_column[(int)((y - y_start) * 1.0 / (line_height) * tex_height)];
		}
		for (int y = 0; y < y_start; y++)
			buffer[y * WIN_WIDTH + i] = 0xff0000;
		for (int y = y_end; y < WIN_HEIGHT; y++)
			buffer[y * WIN_WIDTH + i] = 0x0000ff;
	}
	gettimeofday(&stop, NULL);
	long seconds = stop.tv_sec - start.tv_sec;
	long micros = stop.tv_usec - start.tv_usec;
	long elapsed = seconds * 1000 + micros / 1000;
	int fps = 1000 / elapsed;
	if (fps == 0) {
		int px = WIN_WIDTH - game->numberes[0].width;
		int py = 0;
		put_img(game, game->numberes[0], px, py, buffer);
	}
	else {
		int px = WIN_WIDTH - game->numberes[fps % 10].width;
		int py = 0;
		while (fps > 0) {
			put_img(game, game->numberes[fps % 10], px, py, buffer);
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
		printf("player (%f %f) rot %f\n", game->player_x, game->player_y, game->rot);
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
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	mlx.backbuffer = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	game = (t_game){0};
	game.mlx = mlx;
	game.player_x = 2;
	game.player_y = 2;
	game.rot = 0;
	game.map = (char *[]){
		"111111111111111111111111",
		"100000000001000000000001",
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

	mlx_mouse_hide(mlx.mlx, mlx.win);

	mlx_hook(mlx.win, KeyPress, KeyPressMask, (void *)key_pressed, &game);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, (void *)key_released, &game);
	mlx_loop_hook(mlx.mlx, (void *)test, &game);
	mlx_loop(mlx.mlx);
}