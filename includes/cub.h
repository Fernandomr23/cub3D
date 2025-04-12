/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:58:17 by fmorenil          #+#    #+#             */
/*   Updated: 2025/04/12 13:46:45 by fvizcaya         ###   ########.fr       */
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
	float		x_coord;
	float		y_coord;
	float		x_dirrection;
	float		y_dirrection;
	float		theta;
	float		x_theta;
	float		y_theta;
	float		x_camera;
	float		y_camera;
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
	t_player	*player;
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