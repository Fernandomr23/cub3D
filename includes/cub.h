/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:58:17 by fmorenil          #+#    #+#             */
/*   Updated: 2025/03/18 16:06:57 by fmorenil         ###   ########.fr       */
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

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*title;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	t_map	*map;
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

#endif