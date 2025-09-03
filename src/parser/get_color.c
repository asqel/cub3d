/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:46:38 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/03 17:45:20 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void skip_space_ptr(char **line)
{
	while (ft_is_space(**line))
		(*line)++;
}

static int get_component(char **line, int *err)
{
	int	len;
	int	i;
	int	res;

	*err = 1;
	len = 0;
	while ('0' <= (*line)[len] && (*line)[len] <= '9')
		len++;
	if (len == 0 || len > 3)
		return (c3d_set_err(0, " invalid value", NULL), 0);
	i = 0;
	res = 0;
	while (i < len)
		res = res * 10 + ((*line)[i++] - '0');
	if (res > 255)
		return (c3d_set_err(0, " invalid value", NULL), 0);
	*err = 0;
	*line += len;
	return res;

}

uint32_t	get_color(char *line)
{
	int component[3];
	int err;
	
	line++;
	skip_space_ptr(&line);
	component[0] = get_component(&line, &err);
	skip_space_ptr(&line);
	if (*line != ',' || err)
		return 0xFF000000;
	line++;
	skip_space_ptr(&line);
	component[1] = get_component(&line, &err);
	skip_space_ptr(&line);
	if (*line != ',' || err)
		return 0xFF000000;
	line++;
	skip_space_ptr(&line);
	component[2] = get_component(&line, &err);
	if (err)
		return 0xFF000000;
	return ((component[0] << 16) | (component[1] << 8) | component[2]);
}
