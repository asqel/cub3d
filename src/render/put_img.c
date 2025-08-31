/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:43:24 by axlleres          #+#    #+#             */
/*   Updated: 2025/08/31 18:43:33 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	c3d_put_img(t_game *game, t_img img, int x, int y)
{
	uint32_t	*buffer;
	uint32_t	*column;
	int			i;
	int			k;

	buffer = game->buffer;
	i = -1;
	while (++i < img.width)
	{
		column = &img.data[i * img.height];
		k = -1;
		while (++k < img.height)
		{
			if (column[k] >> 24 == 0)
				buffer[(i + x) + (k + y) * WIN_WIDTH] = column[k];
		}
	}
}
