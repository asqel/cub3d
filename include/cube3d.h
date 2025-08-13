/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:43:16 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/13 11:56:59 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdint.h>

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
	uint32_t *data; // stored in collumns
} t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*backbuffer;
} t_mlx;

typedef struct s_game
{
	t_mlx mlx;
	char **map;
	int map_height;
	int map_width;
	t_img textures[4];
	double player_x;
	double player_y;
	double rot;
	int key_pressed[256]; // w a s d
	t_img numberes[10];
} t_game;

typedef struct s_ray
{
	double x;
	double y;
	double old_x;
	double old_y;
	double rot;
	int face_hit;
	double dist;
	double texture_percent;
} t_ray;

# define DIR_NORTH 0
# define DIR_EAST 1
# define DIR_SOUTH 2
# define DIR_WEST 3

# define WIN_WIDTH 1000
# define WIN_HEIGHT 700

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
char **ft_split_lines(char *text, int *len);

void ft_memcpy(char *dest, const char *src, int len);
int c3d_load_texture(void *mlx, char *path, t_img *img);

#endif
