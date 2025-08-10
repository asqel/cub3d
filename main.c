/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:29:31 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/10 14:27:46 by axlleres         ###   ########.fr       */
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

#define FOV 50.0

int test(void *param) {
	struct timeval start, stop;
	gettimeofday(&start, NULL);
	t_game *game = (t_game *)param;
	t_ray rays[WIN_WIDTH];

	if (game->key_pressed[1])
		game->rot -= M_PI / 180 * 30;
	else if (game->key_pressed[3])
		game->rot += M_PI / 180 * 30;
	if (game->key_pressed[0]) {
		game->player_x += cos(game->rot * M_PI / 180) * 0.04 * (game->key_pressed[10] ? 2 : 1);
		game->player_y += sin(game->rot * M_PI / 180) * 0.04 * (game->key_pressed[10] ? 2 : 1);
	}
	if (game->key_pressed[2]) {
		game->player_x -= cos(game->rot * M_PI / 180) * 0.04 * (game->key_pressed[10] ? 2 : 1);
		game->player_y -= sin(game->rot * M_PI / 180) * 0.04 * (game->key_pressed[10] ? 2 : 1);
	}

	for (int i = 0; i < WIN_WIDTH; i++) {
		rays[i].x = game->player_x;
		rays[i].y = game->player_y;
		rays[i].old_x = game->player_x;
		rays[i].old_y = game->player_y;
		rays[i].face_hit = -1;
		rays[i].dist = 0.0;

		rays[i].rot = game->rot - FOV / 2.0f + (FOV * i / WIN_WIDTH);
		rays[i].rot = rays[i].rot * M_PI / 180.0;
		//printf("rot %f\n", rays[i].rot);
	}

	for (int i = 0; i < WIN_WIDTH; i++) {
		while (1) {
			rays[i].old_x = rays[i].x;
			rays[i].old_y = rays[i].y;

			rays[i].x += cos(rays[i].rot) * 0.01f;
			rays[i].y += sin(rays[i].rot) * 0.01f;

			rays[i].dist += 0.01f;
			float dx = rays[i].x - rays[i].old_x;
			float dy = rays[i].y - rays[i].old_y;

			if (rays[i].x < 0 && dx < 0)
				break;
			if (rays[i].y < 0 && dy < 0)
				break;
			if (rays[i].x >= game->map_width && dx > 0)
				break;
			if (rays[i].y >= game->map_height && dy > 0)
				break;
			if (rays[i].x < 0 || rays[i].y < 0 || rays[i].x >= game->map_width || rays[i].y >= game->map_height)
				continue;
			if (game->map[(int)floor(rays[i].y)][(int)floor(rays[i].x)] == '1') {
				if ((int)floor(rays[i].old_y) == (int)floor(rays[i].y)) {
					rays[i].texture_percent = rays[i].y - (int)floor(rays[i].y);
					if (dx > 0)
						rays[i].face_hit = 0xFF0000; // east
					else
						rays[i].face_hit = 0x00FF00; // west
				}
				else if ((int)floor(rays[i].old_x) == (int)floor(rays[i].x)) {
					rays[i].texture_percent = rays[i].x - (int)floor(rays[i].x);
					if (dy > 0)
						rays[i].face_hit = 0xFF00FF; // south
					else
						rays[i].face_hit = 0x0000FF; // north
				}
				else if (fabs(dx) > fabs(dy)) {
					rays[i].texture_percent = rays[i].x - (int)floor(rays[i].x);
					if (dx > 0)
						rays[i].face_hit = 0xFF0000; // north
					else
						rays[i].face_hit = 0x00FF00; // south
				}
				else {
					rays[i].texture_percent = rays[i].y - (int)rays[i].y;
					if (dy > 0)
						rays[i].face_hit = 0xFF00FF; // west
					else
						rays[i].face_hit = 0x0000FF; // east
				}
				break;
			}
		}
	}
	int tmp;
	uint32_t *buffer = (uint32_t *)mlx_get_data_addr(game->mlx.backbuffer, &tmp, &tmp, &tmp);
	//printf("RAYS\n");
	for (int i = 0; i < WIN_WIDTH; i++) {
		if (rays[i].face_hit == -1) {
			for (int y = 0; y < WIN_HEIGHT; y++)
				buffer[y * WIN_WIDTH + i] = 0x000000;
			continue;
		}
		//printf("Ray %d: x=%.2f, y=%.2f, dist=%.2f, face_hit=%d\n", i, rays[i].x, rays[i].y, rays[i].dist, rays[i].face_hit);
		rays[i].dist = rays[i].dist * cos((i - WIN_WIDTH / 2) * FOV / WIN_WIDTH * M_PI / 180);
		int line_height = ((int)(WIN_WIDTH / (rays[i].dist))) >> 1;
		int y_start = (WIN_HEIGHT - line_height) / 2;
		int y_end = y_start + line_height;
		uint32_t *texture_column = &game->textures[0].data[((int)(game->textures[0].width * rays[i].texture_percent) * game->textures[0].height)];
		int y = y_start;
		if (y < 0)
			y = 0;
		if (y_end > WIN_HEIGHT)
			y_end = WIN_HEIGHT;
		for (; y < y_end; y++) {
			buffer[y * WIN_WIDTH + i] = texture_column[(int)((y - y_start) * 1.0 / (line_height) * game->textures[0].height)];
		}
		for (int y = 0; y < y_start && y < WIN_HEIGHT; y++)
			buffer[y * WIN_WIDTH + i] = 0x000000;
		for (int y = y_end; y < WIN_HEIGHT; y++)
			buffer[y * WIN_WIDTH + i] = 0x000000;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.backbuffer, 0, 0);
	gettimeofday(&stop, NULL);
	long seconds = stop.tv_sec - start.tv_sec;
	long micros = stop.tv_usec - start.tv_usec;
	long elapsed = seconds * 1000 + micros / 1000;
	printf("Frame time: %ld ms as fps %f\n", elapsed, 1000.0 / elapsed);
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
    	"100100000001000011110001",
    	"100001000000000010000001",
    	"100001000100000010000001",
    	"100000000100000000000001",
    	"100011110100011110000001",
    	"100000000000010000000001",
    	"101111111111010111111101",
    	"100000000000000000000001",
    	"100000111111111110000001",
    	"100000100000000010000001",
    	"101110100011110010111101",
    	"100010000000000000100001",
    	"100000000111111000000001",
    	"111111111111111111111111"
	};
	game.map_height = 16;
	game.map_width  = 24;
	c3d_load_texture(mlx.mlx, "assets/grass.xpm", &game.textures[0]);
	c3d_load_texture(mlx.mlx, "assets/grass.xpm", &game.textures[1]);
	c3d_load_texture(mlx.mlx, "assets/grass.xpm", &game.textures[2]);
	c3d_load_texture(mlx.mlx, "assets/grass.xpm", &game.textures[3]);
	mlx_mouse_hide(mlx.mlx, mlx.win);

	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_pressed, &game);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, key_released, &game);
	mlx_loop_hook(mlx.mlx, test, &game);
	mlx_loop(mlx.mlx);
}