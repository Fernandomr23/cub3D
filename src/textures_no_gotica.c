/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:38:38 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/02 23:45:52 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void    ft_texture_init(t_cub *cub)
{
    int	i;

	if (cub->texture_px)
		// liberar cosas
        ;
	cub->texture_px = ft_calloc(HEIGHT + 1,
			sizeof * cub->texture_px);
	if (!cub->texture_px)
        // rutina de salida
        ;
	i = 0;
	while (i < HEIGHT)
	{
		cub->texture_px[i] = ft_calloc(WIDTH + 1,
				sizeof * cub->texture_px);
		if (!cub->texture_px[i])
            // rutina de salida
            ;
		i++;
	}
}

static void ft_texture_index(t_cub *cub)
{
    if (!cub->ray.side)
    {
        if (cub->ray.dir_x < 0)
			cub->texture.index = DIR_W;
		else
			cub->texture.index = DIR_E;
    }
    else
    {
        if (cub->ray.dir_y > 0)
			cub->texture.index = DIR_S;
		else
			cub->texture.index = DIR_N;
    }
}

void    ft_texture_update(t_cub *cub, int x)
{
    int         y;
    int         color;
    t_texture   textr;

    textr = cub->texture;
    ft_texture_index(cub);
    textr.x = cub->ray.wall_x * textr.width;
    if ((!cub->ray.side && cub->ray.dir_x < 0) || 
        (cub->ray.side && cub->ray.dir_y > 0))
        textr.x = textr.width;
    textr.step = 1.0 * textr.width / cub->ray.line_height;
    textr.pos = (cub->ray.draw_start - HEIGHT / 2 +
        cub->ray.line_height / 2) * textr.step;
    y = cub->ray.draw_start;
    while (y < cub->ray.draw_start)
    {
        textr.y = (int)textr.pos & (textr.width -1);
        textr.pos = textr.step;
        color = cub->textures[textr.index][textr.width * textr.y + textr.x];
        if (textr.index == DIR_N || textr.index == DIR_E)
            color = (color >> 1) & 8355711;
        if (color > 0)
            cub->texture_px[y][x] = color;
        y++;
    } 
}
