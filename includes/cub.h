/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:58:17 by fmorenil          #+#    #+#             */
/*   Updated: 2025/04/29 21:00:33 by fvizcaya         ###   ########.fr       */
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

# define ESCAPE 65307
# define KEY_ARROW_L 65361
# define KEY_ARROW_R 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 100
# define KEY_D 115

# define MOVEMENT_SPEED 
# define ROTATION_SPEED

/******************************************************************************
*                           		Structures                                *
******************************************************************************/

typedef struct s_map
{
	int			width;
	int			height;
	double		pos_x;
	double		pos_y;
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
	double	x_dist_lateral;
	double	y_dist_lateral;
	double	x_dist;
	double	y_dist;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef enum e_direction
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
	CW,
	CCW
}	t_direction;

typedef struct s_player
{
	t_direction	direction;
	double		x_coord;
	double		y_coord;
	double		x_direction;
	double		y_direction;
	double		theta;
	double		x_theta;
	double		y_theta;
	double		x_camera;
	double		y_camera;
	double		x_plane;
	double		y_plane;
}	t_player;

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
}	t_cub;

/******************************************************************************
*                           		Functions                                 *
******************************************************************************/

// Read_file

int		ft_read_file(char *str, t_map *map);
int		ft_check_characters(char *str, int *c);
int		ft_check_top_bottom(char *str);
int		ft_check_middle(char *str, char *next);
int		ft_playable(char c);

// Minilib

void	ft_controls(t_cub *data);
int		ft_key_press(int keycode, void *params);
int		ft_close_win(void *params);
int		ft_print_error(char *msg, char *str, int i);

// Movements
int		ft_rotate_player(t_cub *cub, t_direction direction);
int		ft_move_player(t_cub *cub, t_direction direction);
#endif