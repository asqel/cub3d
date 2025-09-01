/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:33:17 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 13:53:08 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <unistd.h>

int	c3d_set_err(int err)
{
	static int	error = 0;

	if (err)
		error = err;
	return (error);
}

char	*c3d_get_err_msg(int err)
{
	static char	*errors[] = {
		"",
		"",
		""
	};

	return (errors[err]);
}

void	c3d_print_err(void)
{
	int	error;

	error = c3d_set_err(0);
	if (error == 42)
		return ((void)perror("cub3d"));
	error = write(STDERR_FILENO, "cub3d: ", 8);
	error = write(STDERR_FILENO, c3d_get_err_msg(error),
			ft_strlen(c3d_get_err_msg(error)));
}
