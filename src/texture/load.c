/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:51:33 by axlleres          #+#    #+#             */
/*   Updated: 2025/07/10 02:25:28 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <mlx.h>

int c3d_load_texture(void *mlx, char *path, t_img *img)
{
	t_img_data	data;
	int			x;
	int			y;

	data.img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (data.img == NULL)
		return (1);
	img->data = malloc(img->width * img->height * sizeof(uint32_t));
	if (img->data == NULL)
		return (mlx_destroy_image(mlx, data.img), NULL);
	data.addr = mlx_get_data_addr(data.img, data.bits_per_pixel,
		data.line_length, data.endian);
	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->height)
			img->data[x + y * img->width] = *(uint32_t *)(data.addr + y * data.line_length + x * (data.bits_per_pixel >> 3));

	}
	mlx_destroy_image(mlx, img);
	return (0);
}
