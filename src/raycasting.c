/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:56:25 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/08 21:30:48 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	ft_create_ray_step(t_cub *cub)
{
	if (cub->ray.dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.x_dist = (cub->player.x_coord - cub->ray.map_x)
			* cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.x_dist = (cub->ray.map_x + 1.0 - cub->player.x_coord)
			* cub->ray.delta_dist_x;
	}
	if (cub->ray.dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.y_dist = (cub->player.y_coord - cub->ray.map_y)
			* cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.y_dist = (cub->ray.map_y + 1.0 - cub->player.y_coord)
			* cub->ray.delta_dist_y;
	}
}

static void	ft_hit(t_cub *cub, int *hit)
{
	while (*hit == 0)
	{
		if (cub->ray.x_dist < cub->ray.y_dist)
		{
			cub->ray.x_dist += cub->ray.delta_dist_x;
			cub->ray.map_x += cub->ray.step_x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.y_dist += cub->ray.delta_dist_y;
			cub->ray.map_y += cub->ray.step_y;
			cub->ray.side = 1;
		}
		if (cub->map->lines[cub->ray.map_y][cub->ray.map_x] == '1')
			*hit = 1;
	}
}

static void	ft_ray_start(t_cub *cub)
{
	if (cub->ray.draw_start < 0)
		cub->ray.draw_start = 0;
	cub->ray.draw_end = cub->ray.line_height / 2 + HEIGHT / 2;
	if (cub->ray.draw_end >= HEIGHT)
		cub->ray.draw_end = HEIGHT - 1;
}

void	ft_raycasting(t_cub *cub, int *x)
{
	int	hit;

	hit = 0;
	cub->ray.camera_x = 2 * (*x) / (double)WIDTH - 1;
	cub->ray.dir_x = cub->player.x_direction + cub->player.x_plane
		* cub->ray.camera_x;
	cub->ray.dir_y = cub->player.y_direction + cub->player.y_plane
		* cub->ray.camera_x;
	cub->ray.map_x = (int)cub->player.x_coord;
	cub->ray.map_y = (int)cub->player.y_coord;
	cub->ray.delta_dist_x = fabs(1 / cub->ray.dir_x);
	cub->ray.delta_dist_y = fabs(1 / cub->ray.dir_y);
	ft_create_ray_step(cub);
	ft_hit(cub, &hit);
	if (!cub->ray.side)
		cub->ray.wall_dist = (cub->ray.map_x - cub->player.x_coord
				+ (1 - cub->ray.step_x) / 2) / cub->ray.dir_x;
	else
		cub->ray.wall_dist = (cub->ray.map_y - cub->player.y_coord
				+ (1 - cub->ray.step_y) / 2) / cub->ray.dir_y;
	cub->ray.line_height = (int)(HEIGHT / cub->ray.wall_dist);
	cub->ray.draw_start = -cub->ray.line_height / 2 + HEIGHT / 2;
	ft_ray_start(cub);
}
