/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:29:31 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/09 16:01:27 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <mlx.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>

int test(void *param) {
	t_game *game = (t_game *)param;
	t_ray rays[WIN_WIDTH];
	mlx_mouse_hide(game->mlx.mlx, game->mlx.win);

	int x, y;
	mlx_mouse_get_pos(game->mlx.mlx, game->mlx.win, &x, &y);
	mlx_mouse_move(game->mlx.mlx, game->mlx.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	int dx = x - (WIN_WIDTH / 2);
	int dy = y - (WIN_HEIGHT / 2);
	if (dx != 0 || dy != 0)
		game->rot += dx * 0.1;

	if (game->key_pressed[4])
		game->rot -= M_PI / 180 * 30;
	else if (game->key_pressed[5])
		game->rot += M_PI / 180 * 30;
	if (game->key_pressed[0]) {
		game->player_x += cos(game->rot * M_PI / 180) * 0.04;
		game->player_y += sin(game->rot * M_PI / 180) * 0.04;
	}
	if (game->key_pressed[2]) {
		game->player_x -= cos(game->rot * M_PI / 180) * 0.04;
		game->player_y -= sin(game->rot * M_PI / 180) * 0.04;
	}
	if (game->key_pressed[1]) {
		game->player_x += cos((game->rot - 90) * M_PI / 180) * 0.04;
		game->player_y += sin((game->rot - 90) * M_PI / 180) * 0.04;
	}
	if (game->key_pressed[3]) {
		game->player_x += cos((game->rot + 90) * M_PI / 180) * 0.04;
		game->player_y += sin((game->rot + 90) * M_PI / 180) * 0.04;
	}

	for (int i = 0; i < WIN_WIDTH; i++) {
		rays[i].x = game->player_x;
		rays[i].y = game->player_y;
		rays[i].old_x = game->player_x;
		rays[i].old_y = game->player_y;
		rays[i].face_hit = -1;
		rays[i].dist = 0.0;

		float fov = 120.0f;
		rays[i].rot = game->rot - fov / 2.0f + (fov * i / WIN_WIDTH);
		//printf("rot %f\n", rays[i].rot);
	}

	for (int i = 0; i < WIN_WIDTH; i++) {
		while (1) {
			rays[i].old_x = rays[i].x;
			rays[i].old_y = rays[i].y;

			rays[i].x += cos(rays[i].rot * M_PI / 180.0f) * 0.05f;
			rays[i].y += sin(rays[i].rot * M_PI / 180.0f) * 0.05f;

			rays[i].dist += 0.05f;
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
			if (game->map[(int)rays[i].y][(int)rays[i].x] == '1') {
				if (fabs(dx) > fabs(dy)) {
					if (dx > 0)
						rays[i].face_hit = 0xFF0000;
					else
						rays[i].face_hit = 0x00FF00;
				}
				else {
					if (dy > 0)
						rays[i].face_hit = 0xFF00FF;
					else
						rays[i].face_hit = 0x0000FF;
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
		int line_height = (int)(WIN_HEIGHT / rays[i].dist);
		int y_start = (WIN_HEIGHT - line_height) / 2;
		int y_end = y_start + line_height;
		for (int y = y_start; y < y_end; y++) {
			if (y < 0 || y >= WIN_HEIGHT) {
				continue;
			}
			buffer[y * WIN_WIDTH + i] = rays[i].face_hit;
		}
		for (int y = 0; y < y_start && y < WIN_HEIGHT; y++)
			buffer[y * WIN_WIDTH + i] = 0x000000;
		for (int y = y_end; y < WIN_HEIGHT; y++)
			buffer[y * WIN_WIDTH + i] = 0x000000;
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
	else if (keycode == XK_q)
		game->key_pressed[4] = 1;
	else if (keycode == XK_e)
		game->key_pressed[5] = 1;
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
	else if (keycode == XK_q)
		game->key_pressed[4] = 0; // q
	else if (keycode == XK_e)
		game->key_pressed[5] = 0;
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
	game.player_x = 1;
	game.player_y = 1;
	game.rot = 0;
	game.map = (char *[]){
		"111111111111111111",
		"100000000000000001",
		"100000000000000001",
		"100000001000000001",
		"100000000000000001",
		"100000000000000001",
		"100010000000000001",
		"100000000000000001",
		"100000000000000001",
		"111111111111111111"
	};
	game.map_height = 10;
	game.map_width = 18;
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