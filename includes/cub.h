/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:58:17 by fmorenil          #+#    #+#             */
/*   Updated: 2025/02/25 10:00:47 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "../libft/libft.h"
#include "../mlx_linux/mlx.h"

/******************************************************************************
*                           		Structures                                *
******************************************************************************/
typedef struct s_cub
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_cub;


/******************************************************************************
*                           		Functions                                 *
******************************************************************************/

int	ft_print_error(char *msg, char *str, int i);