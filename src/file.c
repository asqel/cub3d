/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:02:07 by axlleres          #+#    #+#             */
/*   Updated: 2025/07/09 17:18:42 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cube3d.h"

char	*read_file_fd(int fd, int *size)
{
	char	*content;
	int		alloc_size;
	int		ret;
	char	*tmp;

	alloc_size = 0;
	content = NULL;
	while (1)
	{
		alloc_size += 16;
		tmp = ft_realloc(content, alloc_size, 1);
		if (NULL == tmp)
			return (c3d_set_err(ERR_PERROR), ft_free(content), NULL);
		content = tmp;
		ret = read(fd, &content[*size], 15);
		if (ret == -1)
			return (c3d_set_err(ERR_PERROR), ft_free(content), NULL);
		if (ret == 0)
			break ;
		*size += ret;
		content[*size] = '\0';
	}
	return (content);
}

char	*read_file(char *path)
{
	int		fd;
	char	*content;
	int		size;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (c3d_set_err(ERR_PERROR), NULL);
	size = 0;
	content = read_file_fd(fd, &size);
	close(fd);
	if (content == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (content[i] == 0)
			return (c3d_set_err(ERR_BIN), ft_free(content), NULL);
		i++;
	}
	return (content);
}