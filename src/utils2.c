/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:08:34 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/14 18:33:22 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_characters(char *str, int *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W'
			|| str[i] == ' ' || str[i] == '\t')
		{
			if ((str[i] == 'N' || str[i] == 'S'
					|| str[i] == 'E' || str[i] == 'W'))
				*(c) += 1;
			i++;
		}
		else
			return (0);
	}
	return (1);
}

int	ft_playable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	ft_free(char **ptr)
{
	char	**aux_ptr;
	int		i;

	aux_ptr = (char **) ptr;
	if (!ptr)
		return ;
	i = 0;
	while (aux_ptr[i])
	{
		free(aux_ptr[i]);
		i++;
	}
	free(ptr);
}

int	ft_is_walkable(t_map *map, double x, double y)
{
	if (map->lines[(int)y][(int)x] != '0')
		return (0);
	if (map->lines[(int)(y - C_R)][(int)(x - C_R)] != '0')
		return (0);
	if (map->lines[(int)(y - C_R)][(int)(x + C_R)] != '0')
		return (0);
	if (map->lines[(int)(y + C_R)][(int)(x - C_R)] != '0')
		return (0);
	if (map->lines[(int)(y + C_R)][(int)(x + C_R)] != '0')
		return (0);
	return (1);
}

int	ft_close_win(void *params)
{
	t_cub	*data;
	int		i;

	data = (t_cub *)params;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	i = 0;
	while (i < 4)
	{
		if (data->texture[i].img)
			mlx_destroy_image(data->mlx, data->texture[i].img);
		if (data->texture[i].path)
			free(data->texture[i].path);
		i++;
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->title);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
}
