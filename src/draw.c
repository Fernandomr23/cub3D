/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:27:01 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/12 17:57:52 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_apply_color(t_cub *cub, int x, t_orientation index)
{
	int	y;
	int	aux;
	int	color;

	y = cub->ray.draw_start;
	while (y < cub->ray.draw_end)
	{
		aux = y * 256 - HEIGHT * 128 + cub->ray.line_height * 128;
		cub->texture[index].text_y = ((aux * cub->texture[index].height)
				/ cub->ray.line_height) / 256;
		color = ft_get_color_from_texture(&cub->texture[index],
				cub->texture[index].text_x, cub->texture[index].text_y);
		ft_put_pixel(cub, x, y, color);
		y++;
	}
}

static void	ft_draw_walls(t_cub *cub, t_orientation index, int x)
{
	if (!cub->ray.side)
		cub->texture[index].wall_x = cub->player.y_coord + cub->ray.wall_dist
			* cub->ray.dir_y;
	else
		cub->texture[index].wall_x = cub->player.x_coord + cub->ray.wall_dist
			* cub->ray.dir_x;
	cub->texture[index].wall_x -= floor(cub->texture[index].wall_x);
	cub->texture[index].text_x = (int)(cub->texture[index].wall_x
			* cub->texture[index].width);
	if (!cub->ray.side && cub->ray.dir_x > 0)
		cub->texture[index].text_x = cub->texture[index].width
			- cub->texture[index].text_x - 1;
	if (cub->ray.side && cub->ray.dir_y < 0)
		cub->texture[index].text_x = cub->texture[index].width
			- cub->texture[index].text_x - 1;
	ft_apply_color(cub, x, index);
}

static void	ft_draw_ceiling(t_cub *cub, int x)
{
	int			y;
	t_texture	*tex;

	tex = cub->texture;
	y = 0;
	while (y < cub->ray.draw_start)
	{
		tex[CEILING].text_x = (int)(x * tex[CEILING].width / WIDTH);
		tex[CEILING].text_y = (int)(y * tex[CEILING].height / HEIGHT);
		ft_put_pixel(cub, x, y, cub->cell_color);
		y++;
	}
}

static void	ft_draw_floor(t_cub *cub, int x)
{
	int			y;
	t_texture	*tex;

	tex = cub->texture;
	y = cub->ray.draw_end;
	if (y < 0)
		y = 0;
	else if (y >= HEIGHT)
		cub->ray.draw_end = HEIGHT;
	while (y < HEIGHT)
	{
		tex[FLOOR].text_x = (int)(x * tex[FLOOR].width / WIDTH);
		tex[FLOOR].text_y = (int)(y * tex[FLOOR].height / HEIGHT);
		ft_put_pixel(cub, x, y, cub->floor_color);
		y++;
	}
}

int	ft_draw(t_cub *cub)
{
	int				x;
	t_orientation	tx_index;

	if (ft_load_texture(cub) == -1)
		exit(1);
	x = 0;
	while (x < WIDTH)
	{
		ft_raycasting(cub, &x);
		tx_index = ft_set_texture_index(cub);
		ft_draw_walls(cub, tx_index, x);
		ft_draw_ceiling(cub, x);
		ft_draw_floor(cub, x);
		x++;
	}
	ft_minimap(cub);
	ft_update_player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
