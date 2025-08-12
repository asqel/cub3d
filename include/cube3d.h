/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:43:16 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 17:14:54 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdint.h>
# include "get_next_line.h"

typedef struct s_img_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img_data;

typedef struct s_img
{
	int width;
	int height;
	uint32_t *data;
} t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	wall_textures[4];


} t_mlx;

typedef struct s_game
{
	t_mlx mlx;
	char **map;
	int map_height;
	int map_width;
	char *img_path[4];
	char *flor;
	char *cell;
} t_game;

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

char 	**read_map(char *path);
void	get_texture(t_game *game);
int		check_map(t_game *game);
int		launch_parsing(t_game *game, char *arg);

void	*ft_calloc(size_t size);
void	*ft_realloc(void *ptr, size_t size, int do_zero);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

int		ft_strcount(char *text, int c);
char **ft_split_lines(char *text, int *len);


int	ft_strlen(char *str);
void	skip_spaces(char *str, int *i);
int		ft_is_space(char c);
char	*ft_strdup(const char *s);
char	*ft_substr(char *s, int start, int len);


void prnt_map(char **map);

#endif
