/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:06:37 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/02 23:55:52 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void    ft_init_rcasting(t_cub *cub, int x)
{
    ft_memset(&cub->ray, 0, sizeof(t_ray));
    cub->ray.camera_x = 2 * x / (double) WIDTH - 1;
	cub->ray.dir_x = cub->player.x_direction + cub->player.x_plane * cub->ray.camera_x;
	cub->ray.dir_y = cub->player.y_direction + cub->player.y_plane * cub->ray.camera_x;
	cub->ray.map_x = (int) cub->player.x_coord;
	cub->ray.map_y = (int) cub->player.y_coord;
	cub->ray.x_dist = fabs(1 / cub->ray.dir_x);
	cub->ray.y_dist = fabs(1 / cub->ray.dir_y);
}

void    ft_dda_init(t_cub *cub)
{
    if (cub->ray.dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.x_dist_lateral = (cub->player.x_coord - cub->ray.map_x) * cub->ray.x_dist;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.x_dist_lateral = (cub->ray.map_x + 1.0 - cub->player.x_coord) * cub->ray.x_dist;
	}
	if (cub->ray.dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.y_dist_lateral = (cub->player.y_coord - cub->ray.map_y) * cub->ray.y_dist;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.y_dist_lateral = (cub->ray.map_y + 1.0 - cub->player.y_coord) * cub->ray.y_dist;
	}
}

void    ft_do_raypath(t_cub *cub)
{
    int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub->ray.x_dist_lateral < cub->ray.y_dist_lateral)
		{
			cub->ray.x_dist_lateral += cub->ray.x_dist_lateral;
			cub->ray.map_x += cub->ray.step_x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.y_dist_lateral += cub->ray.y_dist;
			cub->ray.map_y += cub->ray.step_y;
			cub->ray.side = 1;
		}
		if (cub->ray.map_y < 0.25
			|| cub->ray.map_x < 0.25
			|| cub->ray.map_y > cub->map->height - 0.25
			|| cub->ray.map_x > cub->map->width - 1.25)
			break ;
		else if (cub->map->lines[cub->ray.map_y][cub->ray.map_x] > '0')
			hit = 1;
	}
}

void    ft_line_height(t_cub *cub)
{
    if (cub->ray.side == 0)
		cub->ray.wall_dist = (cub->ray.x_dist_lateral - cub->ray.x_dist);
	else
		cub->ray.wall_dist = (cub->ray.y_dist_lateral - cub->ray.y_dist);
	cub->ray.line_height = (int)(HEIGHT / cub->ray.wall_dist);
	cub->ray.draw_start = -(cub->ray.line_height) / 2 + HEIGHT / 2;
	if (cub->ray.draw_start < 0)
		cub->ray.draw_start = 0;
	cub->ray.draw_end = cub->ray.line_height / 2 + HEIGHT / 2;
	if (cub->ray.draw_end >= HEIGHT)
		cub->ray.draw_end = HEIGHT - 1;
	if (cub->ray.side == 0)
		cub->ray.wall_x = cub->player.y_coord + cub->ray.wall_dist * cub->ray.dir_y;
	else
		cub->ray.wall_x = cub->player.x_coord + cub->ray.wall_dist * cub->ray.dir_x;
	cub->ray.wall_x -= floor(cub->ray.wall_x);
}

int ft_raycasting(t_cub *cub)
{
    int x;

    x = 0;
    while (x < WIDTH)
    {
        ft_init_rcasting(cub, x);
        ft_dda_init(cub);
        ft_do_raypath(cub);
		ft_line_height(cub);
//		ft_texture_update(cub, x);
		x++;
	}
	return (1);
}
