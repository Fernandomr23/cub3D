/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:14:03 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/12 17:18:02 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_parse_textures(char *str, t_cub *cub)
{
	char	**splt;

	splt = ft_split(str, ' ');
	if ((*str && *str == '\n') || !splt || !splt[0] || !splt[1])
	{
		ft_free((void **) splt);
		return ;
	}
	if (!ft_strncmp(splt[0], "C", ft_strlen(splt[0])))
		cub->cell_color = ft_parse_color(str);
	else if (!ft_strncmp(splt[0], "F", ft_strlen(splt[0])))
		cub->floor_color = ft_parse_color(str);
	else if (!ft_strncmp(splt[0], "NO", ft_strlen(splt[0])))
		cub->texture[NORTH].path = ft_strdup(splt[1]);
	else if (!ft_strncmp(splt[0], "SO", ft_strlen(splt[0])))
		cub->texture[SOUTH].path = ft_strdup(splt[1]);
	else if (!ft_strncmp(splt[0], "WE", ft_strlen(splt[0])))
		cub->texture[WEST].path = ft_strdup(splt[1]);
	else if (!ft_strncmp(splt[0], "EA", ft_strlen(splt[0])))
		cub->texture[EAST].path = ft_strdup(splt[1]);
	ft_free((void **)splt);
}

static int	ft_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t' || str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_store_texture(t_cub *cub, char *file)
{
	if (!file)
		return (-1);
	if (!ft_only_spaces(file))
		ft_parse_textures(file, cub);
	return (0);
}

int	ft_load_texture(t_cub *cub)
{
	t_texture	*tex;
	int			i;

	tex = cub->texture;
	i = 0;
	while (i < 4)
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
