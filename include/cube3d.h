/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:43:16 by lucmansa          #+#    #+#             */
/*   Updated: 2025/07/09 19:30:21 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <stdio.h>

typedef struct s_img
{
	int width;
	int height;
	void *mlx_img;
} t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*wall_textures[4];
} t_mlx;

# define WIN_HEIGHT 500
# define WIN_WIDTH 500

//err
# define ERR_NONE 0
# define ERR_BIN 1
# define ERR_PERROR 42

//str_utils
int	ft_strlen(char *str);

int		c3d_set_err(int err);
void 	c3d_print_err();

char	*read_file(char *path);

void	*ft_calloc(size_t size);
void	*ft_realloc(void *ptr, size_t size, int do_zero);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

int		ft_strcount(char *text, int c);


#endif
