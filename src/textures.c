/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:41:29 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/09 19:06:14 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static char ft_separation_char(char *str, int *index)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			return (',');
		i++;
	}
	(*index)++;
	return (' ');
}

int	ft_parse_color(char *str)
{
	char	**splt;
	char	c;
	int		i;
	int		rgb[3];

	i = 0;
	c = ft_separation_char(str, &i);
	printf("str: %s\n", str);

	splt = ft_split(str, c);
	if (!splt || !splt[0] || !splt[1] || !splt[2])
		return (-1);
	printf("%s %s %s\n", splt[0], splt[1], splt[2]);
	rgb[0] = ft_atoi(ft_strtrim(splt[0], " "));
	rgb[1] = ft_atoi(ft_strtrim(splt[1], " "));
	rgb[2] = ft_atoi(ft_strtrim(splt[2], " "));
	ft_free((void *) splt);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

static void	ft_parse_textures(char *str, t_cub *cub)
{
	char	**splt;

	splt = ft_split(str, ' ');
	if ((*str && *str == '\n') || !splt)
		return ;
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
	ft_free((void *)splt);
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
	printf("file: %s\n", file);
	if (!file)
		return (-1);
	if (ft_only_spaces(file))
	{
		free(file);
		return (0);
	}
	ft_parse_textures(file, cub);
	return (0);
}


int ft_load_texture(t_cub *cub)
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
inline int	ft_get_color_from_texture(t_texture *texture, int x, int y)
{
	char *px;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	px = texture->data_addr + \
		(y * texture->size_line + x * (texture->bpp / 8));
	return *(unsigned int*) px;
}


