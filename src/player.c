/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:56:33 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/03 18:09:12 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_lines(char	**lines)
{
	int	i;
	int	character;

	i = 0;
	character = 0;
	while (lines[i])
	{
		if (!ft_check_characters(lines[i], &character))
			return (0);
		i++;
	}
	if (character == 0)
		return (ft_print_error("Error: No position for player!", NULL, 0));
	if (character > 1)
		return (ft_print_error("Error: Multiple position for player!", NULL, 0));
	return (1);
}

void ft_find_player(char **lines, t_player *player)
{
	int		i;
	int		j;
	
	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == 'N' || lines[i][j] == 'S'
				|| lines[i][j] == 'E' || lines[i][j] == 'W')
				{
					player->orientation = lines[i][j];
					player->x_coord = j;
					player->y_coord = i;
					return ;
				}
			j++;
		}
		i++;
	}
}

void    ft_init_player(t_player *player)
{
	if (player->orientation == 'N')
	{
		player->x_direction = -1;
		player->y_direction = 0;
	}
	else if (player->orientation == 'S')
	{
		player->x_direction = 1;
		player->y_direction = 0;
	}
	else if (player->orientation == 'E')
	{
		player->x_direction = 0;
		player->y_direction = 1;
	}
	else if (player->orientation == 'W')
	{
		player->x_direction = 0;
		player->y_direction = -1;
	}
	player->x_plane = -player->y_direction * 0.66;
	player->y_plane = player->x_direction * 0.66;
}
