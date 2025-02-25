/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:00:33 by fmorenil          #+#    #+#             */
/*   Updated: 2025/02/25 10:00:40 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_print_error(char *msg, char *str, int i)
{
	if (str)
		printf("%s %s\n", msg, str);
	else
		printf("%s\n", msg);
	return (i);
}