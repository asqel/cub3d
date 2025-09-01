/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:26:34 by axlleres          #+#    #+#             */
/*   Updated: 2025/08/31 18:42:55 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static inline void	tick_movement(t_game *ctx, double speed)
{
	double	forward[2];
	int		mov_dir[2];

	mov_dir[0] = 0;
	mov_dir[1] = 0;
	forward[0] = cos(ctx->rot) * speed;
	forward[1] = sin(ctx->rot) * speed;
	if (ctx->key_pressed[KEY_UP])
		mov_dir[1]++;
	if (ctx->key_pressed[KEY_DOWN])
		mov_dir[1]--;
	if (ctx->key_pressed[KEY_LEFT])
		mov_dir[0]--;
	if (ctx->key_pressed[KEY_RIGHT])
		mov_dir[0]++;
	ctx->p_x += mov_dir[0] * forward[1] + mov_dir[1] * forward[0];
	ctx->p_y += mov_dir[0] * -forward[0] + mov_dir[1] * forward[1];
}

void	c3d_tick(t_game *ctx)
{
	if (ctx->key_pressed[KEY_LOOK_LEFT])
		ctx->rot += M_PI / 180 * 1;
	else if (ctx->key_pressed[KEY_LOOK_RIGHT])
		ctx->rot -= M_PI / 180 * 1;
	tick_movement(ctx, 0.04 * (1 + ctx->key_pressed[KEY_SPRINT]));
}
