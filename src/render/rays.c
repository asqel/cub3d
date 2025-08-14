#include "cube3d.h"

static void init_rays(t_game *game, t_ray *rays, int x, int y) {
	int	i;

	i = WIN_WIDTH;
	while (--i >= 0)
	{
		rays[i].face_hit = -1;
		rays[i].angle = game->rot - ((FOV * i / WIN_WIDTH) - FOV / 2.0f) * M_PI / 180.0;
		rays[i].dirx = cos(rays[i].angle);
		rays[i].diry = sin(rays[i].angle);
		rays[i].map_x = x;
		rays[i].map_y = y;
		rays[i].d_dist_x = 1e30;
		rays[i].d_dist_y = 1e30;
		if (rays[i].dirx)
			rays[i].d_dist_x = fabs(1 / rays[i].dirx);
		if (rays[i].diry)
			rays[i].d_dist_y = fabs(1 / rays[i].diry);
		rays[i].has_hit = 0;
		rays[i].step_x = 1;
		rays[i].step_y = 1;
		if (rays[i].dirx < 0)
			rays[i].step_x = -1;
		if (rays[i].diry < 0)
			rays[i].step_y = -1;
	}
}

void get_ray(t_game *game, t_ray *rays, int x, int y) {
	init_rays(game, rays, x, y);
	for (int i = 0; i < WIN_WIDTH; i++) {
		if(rays[i].dirx < 0)
		{
		  rays[i].side_dist_x = (game->player_x - rays[i].map_x) * rays[i].d_dist_x;
		}
		else
		{
		  rays[i].side_dist_x = (rays[i].map_x + 1.0 - game->player_x) * rays[i].d_dist_x;
		}
		if(rays[i].diry < 0)
		{
		  rays[i].side_dist_y = (game->player_y - rays[i].map_y) * rays[i].d_dist_y;
		}
		else
		{
		  rays[i].side_dist_y = (rays[i].map_y + 1.0 - game->player_y) * rays[i].d_dist_y;
		}
		//perform DDA
		while (!rays[i].has_hit)
		{
			if (rays[i].map_x < 0 && rays[i].dirx < 0)
				break;
			if (rays[i].map_y < 0 && rays[i].diry < 0)
				break;
			if (rays[i].map_x >= game->map_width && rays[i].dirx > 0)
				break;
			if (rays[i].map_y >= game->map_height && rays[i].diry > 0)
				break;
			if(rays[i].side_dist_x < rays[i].side_dist_y)
			{
				rays[i].side_dist_x += rays[i].d_dist_x;
				rays[i].map_x += rays[i].step_x;
				rays[i].hit_horizontal = 0;
			}
			else
			{
				rays[i].side_dist_y += rays[i].d_dist_y;
				rays[i].map_y += rays[i].step_y;
				rays[i].hit_horizontal = 1;
			}
			if (rays[i].map_y < 0 || rays[i].map_x < 0 || rays[i].map_y >= game->map_height || rays[i].map_x >= game->map_width)
				continue;
			if(game->map[rays[i].map_y][rays[i].map_x] == '1')
				rays[i].has_hit = 1;
		}
		if (!rays[i].has_hit)
			continue;
		if(rays[i].hit_horizontal == 0) rays[i].dist = (rays[i].side_dist_x - rays[i].d_dist_x);
      	else          rays[i].dist = (rays[i].side_dist_y - rays[i].d_dist_y);
		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		double wallX; //where exactly the wall was hit
	 	if(rays[i].hit_horizontal == 0) wallX = game->player_y + rays[i].dist * rays[i].diry;
	 	else          wallX = game->player_x + rays[i].dist * rays[i].dirx;
	 	wallX -= floor((wallX));
		rays[i].texture_percent = wallX;
		if(rays[i].hit_horizontal == 0){
			rays[i].dist = (rays[i].side_dist_x - rays[i].d_dist_x);
			rays[i].face_hit = DIR_WEST;
			if (rays[i].dirx > 0) {
				rays[i].texture_percent = 1 - rays[i].texture_percent;
				rays[i].face_hit = DIR_EAST;
			}
		}
		else {
			rays[i].dist = (rays[i].side_dist_y - rays[i].d_dist_y);
			rays[i].face_hit = DIR_NORTH;
			if (rays[i].diry < 0) {
				rays[i].texture_percent = 1 - rays[i].texture_percent;
				rays[i].face_hit = DIR_SOUTH;
			}
		}
		rays[i].dist *= cos(rays[i].angle - game->rot);
		if (rays[i].texture_percent >= 1)
			rays[i].texture_percent = 0.9999;
	}
}