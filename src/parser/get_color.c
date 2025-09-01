/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:46:38 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 15:59:42 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int	ft_atoi(const char *nptr, int *s)
{
	int	nbr;
	int	i;
	int	sign;

	nbr = 0;
	i = 0;
	sign = 1;
	while (nptr[i + *s] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i + *s] == '-' || nptr[i + *s] == '+')
		if (nptr[i++ + *s] == '-')
			sign *= -1;
	while (nptr[i + *s] >= '0' && nptr[i + *s] <= '9')
		nbr = nbr * 10 + (nptr[i++ + *s] - '0');
	s += i;
	return (nbr * sign);
}

uint32_t	get_color(char *line)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (line[i] < '0' || line[i] > '9')
		i++;
	r = ft_atoi(line, &i);
	i ++;
	g = ft_atoi(line, &i);
	i ++;
	b = ft_atoi(line, &i);
	return((r<<16)|(g<<8)|b);
}