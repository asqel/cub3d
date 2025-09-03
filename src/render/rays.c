/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:19:32 by axlleres          #+#    #+#             */
/*   Updated: 2025/09/03 15:17:47 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static inline void	init_rays(t_game *game, t_ray *rays, int x, int y)
{
	int	i;

	i = WIN_WIDTH;
	while (--i >= 0)
	{
		rays[i].face_hit = -1;
		rays[i].angle = game->rot - ((FOV * i / WIN_WIDTH) - FOV / 2)
			* M_PI / 180;
		rays[i].dirx = cos(rays[i].angle);
		rays[i].diry = sin(rays[i].angle);
		rays[i].m_x = x;
		rays[i].m_y = y;
		rays[i].d_dist_x = fabs(1.0 / rays[i].dirx);
		rays[i].d_dist_y = fabs(1.0 / rays[i].diry);
		rays[i].step_x = ((rays[i].dirx >= 0) << 1) - 1;
		rays[i].step_y = ((rays[i].diry >= 0) << 1) - 1;
		if (rays[i].dirx < 0)
			rays[i].sd_x = (game->p_x - rays[i].m_x) * rays[i].d_dist_x;
		else
			rays[i].sd_x = (rays[i].m_x + 1.0 - game->p_x) * rays[i].d_dist_x;
		if (rays[i].diry < 0)
			rays[i].sd_y = (game->p_y - rays[i].m_y) * rays[i].d_dist_y;
		else
			rays[i].sd_y = (rays[i].m_y + 1.0 - game->p_y) * rays[i].d_dist_y;
	}
}

static inline void	get_hit(t_ray *ray, t_game *game)
{
	while (!ray->has_hit)
	{
		if ((ray->m_x < 0 && ray->dirx < 0) || (ray->m_y < 0 && ray->diry < 0)
			|| (ray->m_x >= game->map_width && ray->dirx > 0))
			break ;
		if (ray->m_y >= game->map_height && ray->diry > 0)
			break ;
		if (ray->sd_x < ray->sd_y)
		{
			ray->sd_x += ray->d_dist_x;
			ray->m_x += ray->step_x;
			ray->hit_horizontal = 0;
		}
		else
		{
			ray->sd_y += ray->d_dist_y;
			ray->m_y += ray->step_y;
			ray->hit_horizontal = 1;
		}
		if (ray->m_y < 0 || ray->m_x < 0 || ray->m_y >= game->map_height
			|| ray->m_x >= game->map_width)
			continue ;
		if (game->map[ray->m_y][ray->m_x] == '1')
			ray->has_hit = 1;
	}
}

static void	fix_texture_percent(t_ray *ray)
{
	ray->texture_percent -= floor(ray->texture_percent);
	if (ray->face_hit == DIR_SOUTH || ray->face_hit == DIR_EAST)
		ray->texture_percent = 1 - ray->texture_percent;
}

void	get_ray(t_game *game, t_ray *rays, int x, int y)
{
	int	i;

	init_rays(game, rays, x, y);
	i = WIN_WIDTH;
	while (--i >= 0)
	{
		rays[i].has_hit = 0;
		get_hit(&rays[i], game);
		if (!rays[i].has_hit)
			continue ;
		if (!rays[i].hit_horizontal)
			rays[i].dist = (rays[i].sd_x - rays[i].d_dist_x);
		else
			rays[i].dist = (rays[i].sd_y - rays[i].d_dist_y);
		if (!rays[i].hit_horizontal)
			rays[i].texture_percent = game->p_y + rays[i].dist * rays[i].diry;
		else
			rays[i].texture_percent = game->p_x + rays[i].dist * rays[i].dirx;
		if (!rays[i].hit_horizontal)
			rays[i].face_hit = DIR_WEST - ((rays[i].dirx > 0) << 1);
		else
			rays[i].face_hit = DIR_NORTH + ((rays[i].diry < 0) << 1);
		fix_texture_percent(&rays[i]);
		rays[i].dist *= cos(rays[i].angle - game->rot);
	}
}
