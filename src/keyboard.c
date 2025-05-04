/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodeboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:56:16 by fmorenil          #+#    #+#             */
/*   Updated: 2025/04/03 21:46:10 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void ft_rotate_player(t_cub *cub, int direction)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = cub->player.x_direction;
	if (direction == LEFT)
	{
		cub->player.x_direction = cub->player.x_direction * cos(-ROTATION_SPEED)
			- cub->player.y_direction * sin(-ROTATION_SPEED);
		cub->player.y_direction = old_dir_x * sin(-ROTATION_SPEED)
			+ cub->player.y_direction * cos(-ROTATION_SPEED);
	}
	else if (direction == RIGHT)
	{
		cub->player.x_direction = cub->player.x_direction * cos(ROTATION_SPEED)
			- cub->player.y_direction * sin(ROTATION_SPEED);
		cub->player.y_direction = old_dir_x * sin(ROTATION_SPEED)
			+ cub->player.y_direction * cos(ROTATION_SPEED);
	}
	old_plane_x = cub->player.x_plane;
	cub->player.x_plane = cub->player.x_plane * cos(ROTATION_SPEED)
		- cub->player.y_plane * sin(ROTATION_SPEED);
	cub->player.y_plane = old_plane_x * sin(ROTATION_SPEED)
		+ cub->player.y_plane * cos(ROTATION_SPEED);
}

static void	ft_move_player(t_cub *cub, int direction)
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
		double dir = (direction == RIGHT) ? -1 : 1;
		new_x = cub->player.x_coord + cub->player.y_direction * move_speed * dir;
		new_y = cub->player.y_coord - cub->player.x_direction * move_speed * dir;
		if (cub->map->lines[(int)(cub->player.y_coord)][(int)(new_x)] == '0')
			cub->player.x_coord = new_x;
		if (cub->map->lines[(int)(new_y)][(int)(cub->player.x_coord)] == '0')
			cub->player.y_coord = new_y;
	}
}

int ft_key_release(int keycode, void *params)
{
	t_cub	*cub;

	(void)keycode;
	cub = (t_cub *)params;
	cub->stop = 1;
	return (0);
}

int	ft_key_press(int keycode, void *params)
{
	t_cub	*cub;

	cub = (t_cub *)params;
	if (keycode == ESCAPE || keycode == KEY_ARROW_L || keycode == KEY_ARROW_R
		|| keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D)
	{
		if (keycode == ESCAPE)
			ft_close_win(cub);
		if (keycode == KEY_ARROW_L)
			ft_rotate_player(cub, LEFT);
		if (keycode == KEY_ARROW_R)
			ft_rotate_player(cub, RIGHT);
		if (keycode == KEY_W)
			ft_move_player(cub, FORWARD);
		if (keycode == KEY_S)
			ft_move_player(cub, BACKWARD);
		if (keycode == KEY_A)
			ft_move_player(cub, LEFT);
		if (keycode == KEY_D)
			ft_move_player(cub, RIGHT);

		mlx_destroy_image(cub->mlx, cub->img);
		cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
		if (ft_draw(cub, &cub->ray) == -1)
			return(printf("ERROR: Rendering.\n"), -1);
	}
	return (0);
}
