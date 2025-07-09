/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:22:04 by axlleres          #+#    #+#             */
/*   Updated: 2025/07/09 18:20:30 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cube3d.h"

void	*ft_calloc(size_t size)
{
	void	*ptr;
	size_t	i;

	if (size == 0)
		return (NULL);
	ptr = ft_malloc(size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t n_size, int fill_zero)
{
	void	*new_ptr;
	size_t	min_size;
	size_t	i;
	size_t	o_size;

	if (!ptr && fill_zero)
		return (ft_calloc(n_size));
	if (!ptr && !fill_zero)
		return (ft_malloc(n_size));
	o_size = *(size_t *)((char *)ptr - sizeof(size_t));
	if (o_size == n_size)
		return (ptr);
	new_ptr = ft_malloc(n_size);
	if (!new_ptr)
		return (NULL);
	min_size = o_size;
	if (n_size < o_size)
		min_size = n_size;
	i = -1;
	while (++i < min_size)
		((char *)new_ptr)[i] = ((char *)ptr)[i];
	if (fill_zero)
		while (i < n_size)
			((char *)new_ptr)[i++] = 0;
	return (ft_free(ptr), new_ptr);
}

void	*ft_malloc(size_t size)
{
	char	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size + sizeof(size_t));
	if (!ptr)
		return (NULL);
	*((size_t *)ptr) = size;
	return ((void *)(ptr + sizeof(size_t)));
}

void	ft_free(void *ptr)
{
	if (!ptr)
		return ;
	free((char *)ptr - sizeof(size_t));
}
