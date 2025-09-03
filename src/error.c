/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:33:17 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/03 18:21:54 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <unistd.h>

int	c3d_set_err(int err, char *info, char **get_info)
{
	static int	error = 0;
	static char	*err_info = NULL;

	if (err)
		error = err;
	if (info)
	{
		ft_free(err_info);
		err_info = ft_strdup(info);
	}
	if (get_info)
		*get_info = err_info;
	if (err < 0)
		err_info = NULL;
	return (error);
}

char	*c3d_get_err_msg(int err)
{
	static char	*errors[] = {
		"",
		"Only 1 argument is requiered",
		"Mising texture",
		"Mising floor or ceiling color",
		"Mising wall",
		"Missing player",
		"Texture or color in double",
		"Invalid character in map",
		NULL
	};

	return (errors[err]);
}

void	c3d_print_err(void)
{
	int		error;
	char	*info;

	error = c3d_set_err(0, NULL, NULL);
	if (error == 42)
	{
		write(STDERR_FILENO, "cub3D: ", 7);
		info = NULL;
		c3d_set_err(0, NULL, &info);
		if (info)
			perror(info);
		ft_free(info);
		c3d_set_err(-1, NULL, NULL);
		return ;
	}
	error = write(STDERR_FILENO, "cub3d: ", 8);
	error = write(STDERR_FILENO, c3d_get_err_msg(c3d_set_err(0, NULL, NULL)),
			ft_strlen(c3d_get_err_msg(c3d_set_err(0, NULL, NULL))));
	c3d_set_err(0, NULL, &info);
	if (info)
		error = write(STDERR_FILENO, info, ft_strlen(info));
	ft_free(info);
	c3d_set_err(-1, NULL, NULL);
}
