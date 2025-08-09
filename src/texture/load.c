/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:51:33 by axlleres          #+#    #+#             */
/*   Updated: 2025/08/09 13:52:43 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <mlx.h>

static int convert(t_img_data *data, t_img *img)
{
	int	x;
	int	y;
	int	offset;

	img->data = ft_malloc(sizeof(uint32_t) * img->height * img->width);
	if (img->data == NULL)
		return (1);
	x = -1;
	offset = 0;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->height)
			img->data[offset + y] = *(uint32_t *)(data->addr + y * data->line_length + x * (data->bits_per_pixel >> 3));
		offset += img->width;
	}
	return (0);
}

int c3d_load_texture(void *mlx, char *path, t_img *img)
{
	t_img_data	data;

	data.img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (data.img == NULL)
		return (1);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
		&data.line_length, &data.endian);
	if (convert(&data, img))
		return (mlx_destroy_image(mlx, data.img), 1);
	mlx_destroy_image(mlx, data.img);
	return (0);
}
