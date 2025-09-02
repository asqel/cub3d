#include "cube3d.h"

void	display_fps(t_game *game, int64_t fps)
{
	int	px;
 
	if (fps < 0)
		fps = -fps;
	if (fps == 0)
		c3d_put_img(game, game->textures[TX_NUM_0],
			WIN_WIDTH - game->textures[TX_NUM_0].width, 0);
	else
	{
		px = WIN_WIDTH - game->textures[TX_NUM_0 + (fps % 10)].width;
		while (fps > 0)
		{
			c3d_put_img(game, game->textures[TX_NUM_0 + (fps % 10)], px, 0);
			fps /= 10;
			px -= game->textures[TX_NUM_0 + (fps % 10)].width;
		}
	}
}
