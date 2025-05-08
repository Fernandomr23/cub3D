/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:27:55 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/08 22:22:07 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void ft_draw_square(t_cub *cub, int x, int y, int color)
{
	int i, j;
	for (i = 0; i < MINIMAP_CELL_SIZE; i++)
	{
		for (j = 0; j < MINIMAP_CELL_SIZE; j++)
		{
			ft_put_pixel(cub,
				x + j,
				y + i,
				color);
		}
	}
}

void ft_minimap(t_cub *cub)
{
    int x, y;
    for (y = 0; y < cub->map->height; y++)
    {
        for (x = 0; x < cub->map->width; x++)
        {
            char c = cub->map->lines[y][x];
            int color;
            if (c != '1' && c != '0')
                continue;
            if (c == '1')
                color = 0x000000; // Negro
            else
                color = 0xFFFFFF; // Gris

            ft_draw_square(cub, x * MINIMAP_CELL_SIZE, y * MINIMAP_CELL_SIZE, color);
        }
    }

    // Dibuja al jugador en su celda actual
    int map_x = (int)cub->player.x_coord;
    int map_y = (int)cub->player.y_coord;

    ft_draw_square(cub, map_x * MINIMAP_CELL_SIZE, map_y * MINIMAP_CELL_SIZE, 0x00FF00); // Verde
}
