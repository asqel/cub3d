/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:43:16 by lucmansa          #+#    #+#             */
/*   Updated: 2025/09/01 16:30:33 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# undef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES
#include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include "get_next_line.h"
# include <math.h>
# include <stdlib.h>
# include <mlx.h>

# define FOV 50.0

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

enum e_keys
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPRINT,
	KEY_LOOK_LEFT,
	KEY_LOOK_RIGHT,
	KEY_ENUM_MAX
};

enum e_textures
{
	TX_NORTH,
	TX_EAST,
	TX_SOUTH,
	TX_WEST,
	TX_NUM_0,
	TX_NUM_1,
	TX_NUM_2,
	TX_NUM_3,
	TX_NUM_4,
	TX_NUM_5,
	TX_NUM_6,
	TX_NUM_7,
	TX_NUM_8,
	TX_NUM_9,
	TX_ENUM_MAX
};

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_img
{
	int			width;
	int			height;
	uint32_t	*data;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*backbuffer;
}	t_mlx;

typedef struct s_game
{
	double		p_x;
	double		p_y;
	double		rot;
	t_mlx		mlx;
	uint32_t	*buffer;
	int			key_pressed[KEY_ENUM_MAX];
	t_img		textures[TX_ENUM_MAX];
	uint32_t	ceil_col;
	uint32_t	floor_col;
	char		**map;
	int			map_height;
	int			map_width;
	char		*tx_path[4];
}	t_game;

typedef struct s_ray
{
	double	x;
	double	y;
	int		m_x;
	int		m_y;
	double	angle;
	int		face_hit;
	double	dist;
	double	texture_percent;
	double	dirx;
	double	diry;
	double	hit_horizontal;
	double	d_dist_x;
	double	d_dist_y;
	double	sd_x;
	double	sd_y;
	double	has_hit;
	double	step_x;
	double	step_y;
}	t_ray;

//str_utils
int			ft_strlen(char *str);

int			c3d_set_err(int err);
void		c3d_print_err(void);

char 		**read_map(char *path);
uint32_t	get_color(char *line);
void		get_texture(t_game *game);
void		clean_map(t_game *game);
int			check_map(t_game *game);
int 		get_player(t_game *game);
int			launch_parsing(t_game *game, char *arg);

void		*ft_calloc(size_t size);
void		*ft_realloc(void *ptr, size_t size, int do_zero);
void		*ft_malloc(size_t size);
void		ft_free(void *ptr);

int			ft_strcount(char *text, int c);
char		**ft_split_lines(char *text, int *len);

void		ft_memcpy(char *dest, const char *src, int len);
int			c3d_load_texture(void *mlx, char *path, t_img *img);
void		get_ray(t_game *game, t_ray *rays, int x, int y);
void		c3d_render(t_game *ctx);

void		get_ray(t_game *game, t_ray *rays, int x, int y);
void		c3d_render(t_game *game);
void		c3d_init(t_game *ctx, int argc, char **argv);
void		c3d_tick(t_game *ctx);
void		c3d_put_img(t_game *game, t_img img, int x, int y);

void		c3d_exit(t_game *ctx, int exit_code);

int			ft_strlen(char *str);
void		skip_spaces(char *str, int *i);
int			ft_is_space(char c);
char		*ft_strdup(const char *s);
char		*ft_substr(char *s, int start, int len);


void prnt_map(char **map);

#endif
