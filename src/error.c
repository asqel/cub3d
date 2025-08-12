/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:33:17 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 17:18:51 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <unistd.h>

int	c3d_set_err(int err)
{
	static	int error = 0;

	if (err)
		error = err;
	return (error);
}

char *c3d_get_err_msg(int err)
{
	static char *errors[] = {
		"",
		"",
		""
	};

	return (errors[err]);
}

void c3d_print_err() {
	int error;

	error = c3d_set_err(0);
	if (error == 42)
		return ((void)perror("cube3d"));
	write(STDERR_FILENO, "cube3d: ", 8);
	write(STDERR_FILENO, c3d_get_err_msg(error), ft_strlen(c3d_get_err_msg(error)));
}