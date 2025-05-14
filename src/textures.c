/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:41:29 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/14 18:31:20 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static char	ft_separation_char(char *str, int *index)
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

static int	ft_convert_color(char **splt, int *rgb, int i)
{
	int		j;
	char	*trim;

	j = 0;
	while (j < 3)
	{
		trim = ft_strtrim(splt[i + j], " ");
		if (!trim)
		{
			ft_free(splt);
			return (-1);
		}
		rgb[j] = ft_atoi(trim);
		free(trim);
		j++;
	}
	return (0);
}

static void	ft_remove_letter(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == 'C' || (*str)[i] == 'F')
			(*str)[i] = ' ';
		i++;
	}
}

int	ft_parse_color(char *str)
{
	char	**splt;
	char	c;
	int		i;
	int		rgb[3];

	i = 0;
	c = ft_separation_char(str, &i);
	if (c == ',')
		ft_remove_letter(&str);
	splt = ft_split(str, c);
	if (!splt || !splt[0] || !splt[1] || !splt[2])
	{
		ft_free(splt);
		return (-1);
	}
	if (ft_convert_color(splt, rgb, i) == -1)
		return (-1);
	ft_free(splt);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

inline int	ft_get_color_from_texture(t_texture *texture, int x, int y)
{
	char	*px;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	px = texture->data_addr + \
		(y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int *) px);
}
