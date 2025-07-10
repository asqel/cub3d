/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:22:47 by axlleres          #+#    #+#             */
/*   Updated: 2025/07/09 23:47:21 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int get_line_len(char *text)
{
	int len;

	len = 0;
	while (text[len] != '\0' && text[len] != '\n')
		len++;
	return (len);
}

static int get_line(char *text, int len)
{
	char	*res;

	res = ft_malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	while (len-- > 0)
		res[len] = text[len];
	return (res);
}

char **ft_split_lines(char *text, int *len)
{
	char	**res;
	int		end;
	int		line_len;

	*len = ft_strcount(text, '\n') + 1;
	res = ft_calloc(sizeof(char *) * (1 + *len));
	if (res == NULL)
		return (c3d_set_err(ERR_PERROR), NULL);
	end = 0;
	while (*text != NULL)
	{
		line_len = get_line_len(text);
		res[end] = get_line(text, line_len);
		if (res[end] == NULL)
		{
			ft_free_split(res);
			return (c3d_set_err(ERR_PERROR), NULL);
		}
		text += line_len;
		end++;
		if (*text == '\n')
			text++;
	}
	return (res);
}
