/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:58:17 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/08 20:31:01 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"

/******************************************************************************
*                           		Variables	                              *
******************************************************************************/

# define WIDTH 1920
# define HEIGHT 1080

# define NUM_TEXTURES 6
# define ESCAPE 65307
# define KEY_ARROW_L 65361
# define KEY_ARROW_R 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define MOVEMENT_SPEED 0.1
# define ROTATION_SPEED 0.1
# define COLLISION_RADIUS 0.2

# define LEFT 1
# define RIGHT 2
# define FORWARD 3
# define BACKWARD 4

# define MINIMAP_CELL_SIZE 15


/******************************************************************************
*                           		Structures                                *
******************************************************************************/

typedef struct s_keys
{
	int		left;
	int		right;
	int		forward;
	int		backward;
	int		rotate_left;
	int		rotate_right;
}	t_keys;

typedef	enum	e_orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	CEILING,
	FLOOR
}				t_orientation;
typedef struct s_map
{
	int			height;
	int			width;
	char		**lines;
}	t_map;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	x_dist;
	double	y_dist;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	double		x_coord;
	double		y_coord;
	double		x_direction;
	double		y_direction;
	double		x_plane;
	double		y_plane;
	char		orientation;
}	t_player;

typedef struct s_texture
{
	void			*img;
	char			*data_addr;
	char			*path;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	int				text_x;
	int				text_y;
	double			wall_x;
}	t_texture;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*title;
	char		*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	t_map		*map;
	t_player	player;
	t_ray		ray;
	t_texture	texture[NUM_TEXTURES];
	t_keys		keys;
}	t_cub;

/******************************************************************************
*                           		Functions                                 *
******************************************************************************/

// Read_file

int			ft_read_file(char *str, t_cub *cub, t_map *map);
int			ft_check_lines(char	**lines);
int			ft_map_line(char *str);
int			ft_check_characters(char *str, int *c);
int			ft_check_top_bottom(char *str);
int			ft_check_middle(char *str, char *next, char *prev);
int			ft_playable(char c);
void		ft_init_player(t_player *player);
void 		ft_find_player(char **lines, t_player *player);

// Minilib

void	ft_controls(t_cub *data);
int		ft_key_press(int keycode, void *params);
int 	ft_key_release(int keycode, void *params);
int		ft_close_win(void *params);
int		ft_print_error(char *msg, char *str, int i);

// Raycasting

void	ft_raycasting(t_cub *cub, int *x);

/*
void    ft_init_rcasting(t_cub *cub, int x);
void    ft_dda_init(t_cub *cub);
void    ft_do_raypath(t_cub *cub);
void    ft_line_height(t_cub *cub);
int		ft_raycasting(t_cub *cub);
*/

// Textures
void    ft_texture_init(t_cub *cub);
void    ft_texture_update(t_cub *cub, int x);
int		ft_store_texture(t_cub *cub, char *file);

// Rendering

void    ft_frame_rendering(t_cub *cub);
void    ft_ray_rendering(t_cub *cub);

// Draw pixels
int 	ft_draw(t_cub *cub);
void	ft_put_pixel(t_cub *cub, int x, int y, int color);
int		ft_update_player(t_cub *cub);
void	ft_move_player(t_cub *cub, int direction);
void 	ft_rotate_player(t_cub *cub, int direction);

// Textures

int 			ft_load_texture(t_cub *cub);
t_orientation	ft_set_texture_index(t_cub *cub);
int				ft_get_color_from_texture(t_texture *texture, int x, int y);

// Bonus

void ft_minimap(t_cub *cub);

#endif