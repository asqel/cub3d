/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:34:10 by axlleres          #+#    #+#             */
/*   Updated: 2025/09/02 18:12:35 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "get_next_line.h"

int	ft_strchr(char *s, int c)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

void	ft_strcpy_to_c(const char *src, char *dest, char c)
{
	int	i;

	if (src == NULL || dest == NULL)
		return ;
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == c)
		dest[i++] = c;
	dest[i] = '\0';
}

void	str_append_to_c(char **str, char *append, char c)
{
	int		len1;
	int		len2;
	char	*new_str;

	if (append == NULL)
		return ;
	len1 = 0;
	if (*str != NULL)
		len1 = ft_strchr(*str, '\0');
	len2 = ft_strchr(append, c);
	if (len2 == -1)
		len2 = ft_strchr(append, '\0');
	new_str = ft_malloc(len1 + len2 + 2);
	if (!new_str)
		return ;
	if (*str)
	{
		ft_strcpy_to_c(*str, new_str, '\0');
		ft_free(*str);
	}
	ft_strcpy_to_c(append, new_str + len1, c);
	*str = new_str;
}

int	read_enough(int fd, char **rest)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (-1);
	while (ft_strchr(*rest, '\n') == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_free(buffer);
			return (-1);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		str_append_to_c(rest, buffer, '\0');
	}
	ft_free(buffer);
	return (0);
}

void	str_shift_c(char **str, char c)
{
	char	*new_str;
	int		start;

	if (*str == NULL || **str == '\0')
	{
		ft_free(*str);
		*str = NULL;
		return ;
	}
	start = ft_strchr(*str, c);
	if (start == -1)
		start = ft_strchr(*str, '\0');
	else
		start += 1;
	new_str = ft_malloc(ft_strchr(*str + start, '\0') + 2);
	if (!new_str)
	{
		ft_free(*str);
		*str = NULL;
		return ;
	}
	ft_strcpy_to_c(*str + start, new_str, '\0');
	ft_free(*str);
	*str = new_str;
}
