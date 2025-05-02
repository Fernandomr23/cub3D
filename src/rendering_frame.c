/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:57:15 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/02 23:58:13 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static void	ft_set_image_pixel(t_cub *cub, int x, int y, int color)
{
	int	pixel;

	pixel = y * (cub->size_line / 4) + x;
	cub->data_addr[pixel] = color;
}

static void    ft_set_frame_pixels(t_cub *cub, int x, int y)
{
    if (cub->texture_px[y][x] > 0)
		ft_set_image_pixel(cub->img, x, y, cub->texture_px[y][x]);
	else if (y < WIDTH / 2)
		ft_set_image_pixel(cub->img, x, y, cub->texture.hex_ceiling);
	else if (y < HEIGHT -1)
		ft_set_image_pixel(cub->img, x, y, cub->texture.hex_floor);
}

void    ft_frame_rendering(t_cub *cub)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_set_frame_pixels(cub, x, y);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
    mlx_destroy_image(cub->mlx, cub->img);
}

void    ft_ray_rendering(t_cub *cub)
{
//    ft_texture_init(cub);
    ft_memset(&cub->ray, 0, sizeof (t_ray));
    ft_raycasting(cub);
    ft_frame_rendering(cub);
}
