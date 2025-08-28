#include "cube3d.h"

static inline void fill_color(t_game *ctx, int pos, int len, int color)
{
	while (len-- > 0)
	{
		ctx->buffer[pos] = color;
		pos += WIN_WIDTH;
	}
}

static inline void copy_wall(t_game *ctx, int pos, int len, t_ray *ray)
{
	uint32_t	*column;
	double		step;
	double		i;

	column = &ctx->textures[ray->face_hit].data[((int)(ctx->textures[ray->face_hit].width * ray->texture_percent) * ctx->textures[ray->face_hit].height)];
	i = 0;
	step = ctx->textures[ray->face_hit].height / len;
	while (len-- > 0)
	{
		if (pos >= WIN_WIDTH * WIN_HEIGHT)
			break;
		if (pos >= 0)
			ctx->buffer[pos] = column[(int)i];
		pos += WIN_WIDTH;
		i += step;
	}
}

static inline void do_wall_ceil_floor(t_game *ctx, int x, int ceil_end, int floor_start)
{
	if (ceil_end > 0)
		fill_color(ctx, x, ceil_end, 0xff0000);
	if (floor_start < WIN_HEIGHT)
		fill_color(ctx, x + floor_start * WIN_WIDTH, WIN_HEIGHT - floor_start, 0x00ff00);
}

static inline void draw_wall(t_game *ctx, int x, t_ray *ray)
{
	int height;
	int	y_start;
	int	y_end;

	height = ((int)(WIN_HEIGHT / (ray->dist)));
	y_start = (WIN_HEIGHT - height) / 2;
	y_end = y_start + height;
	do_wall_ceil_floor(ctx, x, y_start, y_end);
	copy_wall(ctx, y_start * WIN_WIDTH + x, height, ray);
}

void c3d_render(t_game *ctx)
{
	t_ray	rays[WIN_WIDTH];
	int		i;

	get_ray(ctx, rays, (int)ctx->player_x, (int)ctx->player_y);
	i = WIN_WIDTH;
	while (i-- > 0)
	{
		if (rays[i].face_hit == -1 || rays[i].dist <= 0)
		{
			fill_color(ctx, i, WIN_HEIGHT / 2, 0xFF0000);
			fill_color(ctx, i + WIN_HEIGHT / 2 * WIN_WIDTH, WIN_HEIGHT / 2, 0x00FF00);
			continue;
		}
		draw_wall(ctx, i, &rays[i]);
	}

}