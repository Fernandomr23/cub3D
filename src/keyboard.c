/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:56:16 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/08 21:32:13 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_key_release(int keycode, void *params)
{
	t_cub	*cub;

	cub = (t_cub *)params;
	if (keycode == KEY_W)
		cub->keys.forward = 0;
	if (keycode == KEY_S)
		cub->keys.backward = 0;
	if (keycode == KEY_A)
		cub->keys.left = 0;
	if (keycode == KEY_D)
		cub->keys.right = 0;
	if (keycode == KEY_ARROW_L)
		cub->keys.rotate_left = 0;
	if (keycode == KEY_ARROW_R)
		cub->keys.rotate_right = 0;
	return (0);
}

int	ft_key_press(int keycode, void *params)
{
	t_cub	*cub;

	cub = (t_cub *)params;
	if (keycode == ESCAPE)
		ft_close_win(cub);
	if (keycode == KEY_W)
		cub->keys.forward = 1;
	if (keycode == KEY_S)
		cub->keys.backward = 1;
	if (keycode == KEY_A)
		cub->keys.left = 1;
	if (keycode == KEY_D)
		cub->keys.right = 1;
	if (keycode == KEY_ARROW_L)
		cub->keys.rotate_left = 1;
	if (keycode == KEY_ARROW_R)
		cub->keys.rotate_right = 1;
	return (0);
}
