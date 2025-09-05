/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:24:25 by axlleres          #+#    #+#             */
/*   Updated: 2025/09/05 20:18:30 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static inline void	fill_color(t_game *ctx, int pos, int len, int color)
{
	while (len-- > 0)
	{
		ctx->buffer[pos] = color;
		pos += WIN_WIDTH;
	}
}

static inline void	copy_wall(t_game *ctx, int pos, int len, t_ray *ray)
{
	uint32_t	*column;
	double		step;
	double		i;

	column = &ctx->textures[ray->face_hit].data[
		((int)(ctx->textures[ray->face_hit].width * ray->texture_percent)
			* ctx->textures[ray->face_hit].height)];
	step = ctx->textures[ray->face_hit].height * 1.0 / len;
	i = 0;
	if (pos < 0)
	{
		i = (-pos / WIN_WIDTH + 1);
		pos += i * WIN_WIDTH;
		i *= step;
	}
	while (len-- > 0 && pos < WIN_WIDTH * WIN_HEIGHT)
	{
		ctx->buffer[pos] = column[(int)i];
		pos += WIN_WIDTH;
		i += step;
	}
}

static inline void	do_wall_ceil_floor(t_game *ctx, int x, int ceil_end,
	int floor_start)
{
	if (ceil_end > 0)
		fill_color(ctx, x, ceil_end, ctx->ceil_col);
	if (floor_start < WIN_HEIGHT)
		fill_color(ctx, x + floor_start * WIN_WIDTH, WIN_HEIGHT - floor_start,
			ctx->floor_col);
}

static inline void	draw_wall(t_game *ctx, int x, t_ray *ray)
{
	int		height;
	int		y_start;
	int		y_end;
	double	d_height;

	d_height = WIN_HEIGHT / ray->dist;
	if (d_height >= 0x2FFFFF - 2)
		height = 0x2FFFFF - 2;
	else
		height = (int)d_height;
	y_start = (WIN_HEIGHT - height) / 2;
	y_end = y_start + height;
	do_wall_ceil_floor(ctx, x, y_start, y_end);
	if (height > 0)
		copy_wall(ctx, y_start * WIN_WIDTH + x, height, ray);
}

void	c3d_render(t_game *ctx)
{
	t_ray	rays[WIN_WIDTH];
	int		i;

	get_ray(ctx, rays, floor(ctx->p_x), floor(ctx->p_y));
	i = WIN_WIDTH;
	while (i-- > 0)
	{
		if (rays[i].face_hit == -1 || rays[i].dist <= 0)
		{
			fill_color(ctx, i, WIN_HEIGHT / 2, ctx->ceil_col);
			fill_color(ctx, i + WIN_HEIGHT / 2 * WIN_WIDTH, WIN_HEIGHT / 2,
				ctx->floor_col);
			continue ;
		}
		draw_wall(ctx, i, &rays[i]);
	}
}
