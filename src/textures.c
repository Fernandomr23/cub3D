/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:41:29 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/07 16:14:35 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int ft_load_texture(t_cub *cub)
{
	t_texture	*tex;
	int			i;

	tex = cub->texture;
	// Apaño hasta que se copien las texturas en el parseo
	tex[0].path = ft_strdup("textures/bookshelf_01.xpm");
	tex[1].path = ft_strdup("textures/bookshelf_02.xpm");
	tex[2].path = ft_strdup("textures/bookshelf_03.xpm");
	tex[3].path = ft_strdup("textures/bookshelf.xpm");
	tex[4].path = ft_strdup("textures/basalt_top.xpm");
	tex[5].path = ft_strdup("textures/netherrack.xpm");

	i = 0;
	while (i < NUM_TEXTURES)
	{
		tex[i].img = mlx_xpm_file_to_image(cub->mlx, \
			tex[i].path, &tex[i].width, &tex[i].height);
		if (!tex[i].img)
			return (printf("ERROR loading xpm file to image.\n"), -1);
		tex[i].data_addr = mlx_get_data_addr(tex[i].img, \
			&tex[i].bpp, &tex[i].size_line, &tex[i].endian);
		if (!tex[i].data_addr)
			return (printf("ERROR getting data addresss.\n"), -1);
		i++;
	}
	return (0);
}

t_orientation	ft_set_texture_index(t_cub *cub)
{
	if (!cub->ray.side)
	{
		if (cub->ray.dir_x > 0)
			return (NORTH);
		else 
			return (SOUTH);
	}
	else 
	{
		if (cub->ray.dir_y > 0)
			return (WEST);
		else
			return (EAST);
	}
}
inline int	ft_get_color_from_texture(t_texture *texture, int x, int y)
{
	char *px;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return 0x000000;
	px = texture->data_addr + \
		(y * texture->size_line + x * (texture->bpp / 8));
	return *(unsigned int*) px;
}


