/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:00:33 by fmorenil          #+#    #+#             */
/*   Updated: 2025/03/18 15:48:56 by fmorenil         ###   ########.fr       */
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
			if ((str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W'))
				*(c) += 1;
			i++;
		}
		else
			return (ft_print_error("Error in line:", str, 0));
	}
	return (1);
}
