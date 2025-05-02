/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:10:34 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/05/02 19:35:14 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int	ft_rotate_player(t_cub *cub, t_direction direction)
// {
// 	float	swap;
// 	float	x_theta;
// 	float	y_theta;
// 	float	theta;

// 	if (!cub)
// 		return (-1);
// 	x_theta = cub->player->x_theta;
// 	y_theta = cub->player->y_theta;
// 	if (direction == CW)
// 		cub->player->theta++;
// 	else if (direction == CCW)
// 		cub->player->theta--;
// 	theta = cub->player->theta;
// 	swap = x_theta;
// 	cub->player->x_theta = x_theta * cos(theta) - y_theta * sin(theta);
// 	cub->player->y_theta = swap * sin(theta) + y_theta * cos(theta);
// 	return (0);
// }

// int	ft_move_player(t_cub *cub, t_direction direction)
// {
// 	if (!cub)
// 		return (-1);
// 	if (direction == DIR_N)
// 		cub->player->y_coord++;
// 	else if (direction == DIR_S)
// 		cub->player->y_coord--;
// 	else if (direction == DIR_E)
// 		cub->player->x_coord++;
// 	else if (direction == DIR_W)
// 		cub->player->y_coord--;
// 	return (0);
// }

