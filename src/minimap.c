/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:27:55 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/12 18:15:05 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_CELL_SIZE)
	{
		j = 0;
		while (j < MINIMAP_CELL_SIZE)
		{
			ft_put_pixel(cub, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	ft_draw_player(t_cub *cub)
{
	int	map_x;
	int	map_y;

	map_x = (int)cub->player.x_coord;
	map_y = (int)cub->player.y_coord;
	ft_draw_square(cub, map_x * MINIMAP_CELL_SIZE,
		map_y * MINIMAP_CELL_SIZE, 0x00FF00);
}

void	ft_minimap(t_cub *cub)
{
	char	c;
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < ft_strlen(cub->map->lines[y]))
		{
			c = cub->map->lines[y][x];
			if (c == '1' || c == '0')
			{
				color = 0xFFFFFF;
				if (c == '1')
					color = 0x000000;
				ft_draw_square(cub, x * MINIMAP_CELL_SIZE,
					y * MINIMAP_CELL_SIZE, color);
			}
			x++;
		}
		y++;
	}
	ft_draw_player(cub);
}
