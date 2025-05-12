/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:42:42 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/12 18:19:18 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_rotate_player(t_cub *cub, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	if (direction == LEFT)
		angle = -ROTATION_SPEED;
	else
		angle = ROTATION_SPEED;
	old_dir_x = cub->player.x_direction;
	cub->player.x_direction = cub->player.x_direction * cos(angle)
		- cub->player.y_direction * sin(angle);
	cub->player.y_direction = old_dir_x * sin(angle)
		+ cub->player.y_direction * cos(angle);
	old_plane_x = cub->player.x_plane;
	cub->player.x_plane = cub->player.x_plane * cos(angle)
		- cub->player.y_plane * sin(angle);
	cub->player.y_plane = old_plane_x * sin(angle)
		+ cub->player.y_plane * cos(angle);
}

static void	ft_move_x(t_cub *cub, int direction)
{
	double	new_x;
	double	new_y;
	double	dir;

	if (direction == FORWARD)
		dir = 1;
	else
		dir = -1;
	new_x = cub->player.x_coord + cub->player.x_direction
		* MOVEMENT_SPEED * dir;
	new_y = cub->player.y_coord + cub->player.y_direction
		* MOVEMENT_SPEED * dir;
	if (ft_is_walkable(cub->map, new_x, cub->player.y_coord))
		cub->player.x_coord = new_x;
	if (ft_is_walkable(cub->map, cub->player.x_coord, new_y))
		cub->player.y_coord = new_y;
}

static void	ft_move_y(t_cub *cub, int direction)
{
	double	new_x;
	double	new_y;
	double	dir;

	if (direction == LEFT)
		dir = -1;
	else
		dir = 1;
	new_x = cub->player.x_coord + cub->player.x_plane
		* MOVEMENT_SPEED * dir;
	new_y = cub->player.y_coord + cub->player.y_plane
		* MOVEMENT_SPEED * dir;
	if (ft_is_walkable(cub->map, new_x, cub->player.y_coord))
		cub->player.x_coord = new_x;
	if (ft_is_walkable(cub->map, cub->player.x_coord, new_y))
		cub->player.y_coord = new_y;
}

void	ft_move_player(t_cub *cub, int direction)
{
	if (direction == FORWARD || direction == BACKWARD)
		ft_move_x(cub, direction);
	else if (direction == LEFT || direction == RIGHT)
	{
		ft_move_y(cub, direction);
	}
}

void	ft_controls(t_cub *data)
{
	mlx_hook(data->win, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->win, 3, 1L << 1, ft_key_release, data);
	mlx_hook(data->win, 17, 0, ft_close_win, data);
}
