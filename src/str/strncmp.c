/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:47:23 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/03 16:47:34 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	p;

	p = 0;
	while (p < n && s1[p] != '\0' && s2[p] != '\0')
	{
		if (s1[p] != s2[p])
			return ((unsigned char)s1[p] - (unsigned char)s2[p]);
		p++;
	}
	if (p == n)
		return (0);
	return ((unsigned char)s1[p] - (unsigned char)s2[p]);
}