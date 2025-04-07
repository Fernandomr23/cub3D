/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodeboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:56:16 by fmorenil          #+#    #+#             */
/*   Updated: 2025/04/03 21:46:10 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_key_press(int keycode, void *params)
{
	t_cub	*cub;

	cub = (t_cub *)params;
	if (keycode == ESCAPE)
		ft_close_win(cub);
	if (keycode == KEY_ARROW_L)
		ft_rotate_player(cub, CW);
	if (keycode == KEY_ARROW_R)
		ft_rotate_player(cub, CCW);
	if (keycode == KEY_W)
		ft_move_player(cub, DIR_N);
	if (keycode == KEY_A)
		ft_move_player(cub, DIR_E);
	if (keycode == KEY_S)
		ft_move_player(cub, DIR_S);
	if (keycode == KEY_D)
		ft_move_player(cub, DIR_W);
	return (0);
}
