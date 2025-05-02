/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:27:01 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/02 23:13:33 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// static void put_pixel_to_image(t_cub *cub, int x, int y, int color)
// {
//     if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
//     {
//         char *dst = cub->data_addr + (y * cub->size_line + x * (cub->bpp / 8));
//         *(unsigned int *)dst = color;
//     }
// }

// // Dibujar la pantalla completa
// void draw_screen(t_cub *cub)
// {
//     ft_memset(cub->data_addr, 0, HEIGHT * cub->size_line);

//     ft_do_raycasting(cub);

//     mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
// }