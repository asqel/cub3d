/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:51:33 by axlleres          #+#    #+#             */
/*   Updated: 2025/07/09 18:00:31 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <mlx.h>

int c3d_load_texture(void *mlx, char *path, t_img *img)
{
	void *texture;

	texture = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (texture == NULL)
		return (1);
	img->mlx_img = texture;
	return (0);
}
