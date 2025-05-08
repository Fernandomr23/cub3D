/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:41:29 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/08 22:29:19 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_parse_color(char *str)
{
	char	**splt;
	int		rgb[3];

	splt = ft_split(str, ',');
	if (!splt)
		return (-1);
	printf("%s %s %s\n", splt[1], splt[2], splt[3]);
	rgb[0] = ft_atoi(ft_strtrim(splt[1], " "));
	rgb[1] = ft_atoi(ft_strtrim(splt[2], " "));
	rgb[2] = ft_atoi(ft_strtrim(splt[3], " "));
	ft_free((void *) splt);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[0]);
}

t_orientation	ft_parse_textures(char *str)
{
	char	**splt;

	printf("Antes de split\n");
	splt = ft_split(str, ' ');
	if (*str && *str == '\n')
		return (-1);
	if (!splt)
		return (-1);
	printf("Despues de split\n");
	if (!ft_strncmp(splt[0], "C", ft_strlen(splt[0])))
		return (CEILING);
	else if (!ft_strncmp(splt[0], "F", ft_strlen(splt[0])))
		return (FLOOR);
	else if (!ft_strncmp(splt[0], "NO", ft_strlen(splt[0])))
		return (NORTH);
	else if (!ft_strncmp(splt[0], "SO", ft_strlen(splt[0])))
		return (SOUTH);
	else if (!ft_strncmp(splt[0], "WE", ft_strlen(splt[0])))
		return (WEST);
	else if (!ft_strncmp(splt[0], "EA", ft_strlen(splt[0])))
		return (EAST);
	return (-1);
}

int ft_store_texture(t_cub *cub, char *file)
{
	int		tex_index;
	int		color;

	printf("TRACE 1\n");
	if (!file)
		return (-1);
	tex_index = ft_parse_textures(file);
	printf("TRACE 2\n");
	printf("====> %d\n", tex_index);
	if (tex_index == -1)
		return (-1);
	if (tex_index < CEILING)
	{
		cub->texture[tex_index].path = ft_strdup(file);
	}
	else
	{
		color = ft_parse_color(file);
		if (color == -1)
			return (-1);
		if (tex_index == CEILING)
			cub->cell_color = color;
		else if (tex_index == FLOOR)
			cub->floor_color = color;
	}
	return (0);
}

int ft_load_texture(t_cub *cub)
{
	t_texture	*tex;
	int			i;

	tex = cub->texture;
	// Apaño hasta que se copien las texturas en el parseo
	/*
	tex[0].path = ft_strdup("textures/bookshelf_01.xpm");
	tex[1].path = ft_strdup("textures/bookshelf_02.xpm");
	tex[2].path = ft_strdup("textures/bookshelf_03.xpm");
	tex[3].path = ft_strdup("textures/bookshelf.xpm");
	tex[4].path = ft_strdup("textures/basalt_top.xpm");
	tex[5].path = ft_strdup("textures/netherrack.xpm");
	*/

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
		return (0);
	px = texture->data_addr + \
		(y * texture->size_line + x * (texture->bpp / 8));
	return *(unsigned int*) px;
}


