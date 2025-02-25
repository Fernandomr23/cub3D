/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:56:16 by fmorenil          #+#    #+#             */
/*   Updated: 2025/02/25 11:02:45 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_key_press(int keycode, void *params)
{
	t_cub	*data;

	data = (t_cub *)params;
	if (keycode == ESCAPE)
		ft_close_win(data);
	return (0);
}
