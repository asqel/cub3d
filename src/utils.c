/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:20:44 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 15:59:58 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

void	skip_spaces(char *str, int *i)
{
	while (ft_is_space(str[*i]))
		(*i)++;
}

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\f'  || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	return (0);
}
char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (res);
	len = 0;
	while (s[len] != '\0')
	{
		res[len] = s[len];
		len++;
	}
	res[len] = '\0';
	return (res);
}
