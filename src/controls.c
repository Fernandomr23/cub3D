/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:42:42 by fmorenil          #+#    #+#             */
/*   Updated: 2025/02/25 10:55:33 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_close_win(void *params)
{
	t_cub	*data;

	data = (t_cub *)params;
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->title);
	free(data->mlx);
	free(data);
	exit(0);
}

void	ft_controls(t_cub *data)
{
	mlx_hook(data->win, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->win, 17, 0, ft_close_win, data);
}
