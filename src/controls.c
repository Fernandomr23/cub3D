/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:42:42 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/07 16:32:54 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void	ft_rotate_player(t_cub *cub, int direction)
{
	double old_dir_x;
	double old_plane_x;
	double angle;

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

void	ft_move_player(t_cub *cub, int direction)
{
	double	new_x;
	double	new_y;

	double move_speed = MOVEMENT_SPEED;
	if (direction == FORWARD || direction == BACKWARD)
	{
		double dir = (direction == FORWARD) ? 1 : -1;
		new_x = cub->player.x_coord + cub->player.x_direction * move_speed * dir;
		new_y = cub->player.y_coord + cub->player.y_direction * move_speed * dir;

		if (cub->map->lines[(int)(cub->player.y_coord)][(int)(new_x)] == '0')
			cub->player.x_coord = new_x;
		if (cub->map->lines[(int)(new_y)][(int)(cub->player.x_coord)] == '0')
			cub->player.y_coord = new_y;
	}
	else if (direction == LEFT || direction == RIGHT)
	{
		double dir = (direction == LEFT) ? -1 : 1;
		new_x = cub->player.x_coord + cub->player.x_plane * move_speed * dir;
		new_y = cub->player.y_coord + cub->player.y_plane * move_speed * dir;

		if (cub->map->lines[(int)(cub->player.y_coord)][(int)(new_x)] == '0')
			cub->player.x_coord = new_x;
		if (cub->map->lines[(int)(new_y)][(int)(cub->player.x_coord)] == '0')
			cub->player.y_coord = new_y;
	}
}

int	ft_close_win(void *params)
{
	t_cub	*data;

	data = (t_cub *)params;
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->title);
	free(data->mlx);
	free(data);
	exit(0);
}

void	ft_controls(t_cub *data)
{
	mlx_hook(data->win, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->win, 3, 1L << 1, ft_key_release, data);
	mlx_hook(data->win, 17, 0, ft_close_win, data);
}
