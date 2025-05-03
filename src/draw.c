/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:27:01 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/03 20:55:41 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>

void	ft_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst; 
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
    dst = cub->data_addr + (y * cub->size_line + x * (cub->bpp / 8));
	*(unsigned int *)dst = color;
}

static void ft_draw_line(t_cub *cub, int x, int start, int end, int color)
{
    int y;

    y = start;
    if (y < 0)
        y = 0;
    if (end > HEIGHT)
        end = HEIGHT;
    while (y < end)
    {
        ft_put_pixel(cub, x, y, color);
        y++;
    }
}

static int  ft_get_color_from_texture(t_texture *texture, int x, int y)
{
    char *dst;

    dst = texture->data_addr + (y * texture->size_line + x * (texture->bpp / 8));
    return *(unsigned int*) dst;
}

static void ft_load_texture(t_cub *cub)
{
    cub->texture.img = mlx_xpm_file_to_image(cub->mlx, "blue_stone.xpm", &cub->texture.width, &cub->texture.height);
    if (!cub->texture.img)
    {
        printf("ERROR loading xpm file to image.\n");
        return ;
    }
    cub->texture.data_addr = mlx_get_data_addr(cub->texture.img, &cub->texture.bpp, &cub->texture.size_line, &cub->texture.endianess);
    if (!cub->texture.data_addr)
    {
        printf("ERROR getting data addresss.\n");
        return ;
    }
}

void ft_draw(t_cub *cub, t_ray *ray)
{
    int x;
    int hit;
    int color;
    
    x = 0;
    while (x < WIDTH)
    {
        ray->camera_x = 2 * x / (double)WIDTH - 1;
        ray->dir_x = cub->player.x_direction + cub->player.x_plane * ray->camera_x;
        ray->dir_y = cub->player.y_direction + cub->player.y_plane * ray->camera_x;
        
        ray->map_x = (int)cub->player.x_coord;
        ray->map_y = (int)cub->player.y_coord;
        
        ray->delta_dist_x = fabs(1 / ray->dir_x);
        ray->delta_dist_y = fabs(1 / ray->dir_y);
        
        hit = 0;
        if (ray->dir_x < 0)
        {
            ray->step_x = -1;
            ray->x_dist = (cub->player.x_coord - ray->map_x) * ray->delta_dist_x;
        }
        else
        {
            ray->step_x = 1;
            ray->x_dist = (ray->map_x + 1.0 - cub->player.x_coord) * ray->delta_dist_x;
        }
        
        if (ray->dir_y < 0)
        {
            ray->step_y = -1;
            ray->y_dist = (cub->player.y_coord - ray->map_y) * ray->delta_dist_y;
        }
        else
        {
            ray->step_y = 1;
            ray->y_dist = (ray->map_y + 1.0 - cub->player.y_coord) * ray->delta_dist_y;
        }

        while (hit == 0)
        {
            if (ray->x_dist < ray->y_dist)
            {
                ray->x_dist += ray->delta_dist_x;
                ray->map_x += ray->step_x;
                ray->side = 0;
            }
            else
            {
                ray->y_dist += ray->delta_dist_y;
                ray->map_y += ray->step_y;
                ray->side = 1;
            }
            // Check if the ray has hit a wall
            if (cub->map->lines[ray->map_y][ray->map_x] == '1')
                hit = 1;
        }

        if (ray->side == 0)
            ray->wall_dist = (ray->map_x - cub->player.x_coord + (1 - ray->step_x) / 2) / ray->dir_x;
        else
            ray->wall_dist = (ray->map_y - cub->player.y_coord + (1 - ray->step_y) / 2) / ray->dir_y;
        
        ray->line_height = (int)(HEIGHT / ray->wall_dist);
        ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
        if (ray->draw_start < 0)
            ray->draw_start = 0;
        ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
        if (ray->draw_end >= HEIGHT)
            ray->draw_end = HEIGHT - 1;
        /*
        if (ray->side == 1)
            color = 0xFF0000; // Red for vertical walls
        else
            color = 0x800000; // Green for horizontal walls
        ft_draw_line(cub, x, ray->draw_start, ray->draw_end, color);
        */
        ft_load_texture(cub);
        (void) color;
        if (!cub->ray.side)
            cub->texture.wall_x = cub->player.y_coord + cub->ray.wall_dist * cub->ray.dir_y;
        else
            cub->texture.wall_x = cub->player.x_coord + cub->ray.wall_dist * cub->ray.dir_x;
        cub->texture.wall_x -= floor(cub->texture.wall_x);
        cub->texture.text_x = (int) (cub->texture.wall_x + (double) cub->texture.width);
        if (!cub->ray.side && cub->ray.dir_x > 0)
            cub->texture.text_x = cub->texture.width - cub->texture.text_x - 1;
        if (cub->ray.side && cub->ray.dir_y < 0)
            cub->texture.text_x = cub->texture.width - cub->texture.text_x - 1;
        int i = cub->ray.draw_start;
        int d;
        while (i < cub->ray.draw_end)
        {
            d = i * 256 - HEIGHT * 128 + cub->ray.line_height * 128;
            cub->texture.text_y = ((d * cub->texture.height) / cub->ray.line_height) / 256;
            color = ft_get_color_from_texture(&cub->texture, cub->texture.text_x, cub->texture.text_y);
            i++;
        }
        // Ceiling
        ft_draw_line(cub, x, 0, ray->draw_start - 1, 0x87CEEB);
        // Floor
        ft_draw_line(cub, x, ray->draw_end + 1, HEIGHT - 1, 0x8B4513);
        x++;
    }
    mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}