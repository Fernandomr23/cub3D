/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:00:33 by fmorenil          #+#    #+#             */
/*   Updated: 2025/03/11 12:15:41 by fmorenil         ###   ########.fr       */
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

int	ft_check_characters(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W'
			|| str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}