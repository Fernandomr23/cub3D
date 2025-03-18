/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:00:33 by fmorenil          #+#    #+#             */
/*   Updated: 2025/03/18 16:05:05 by fmorenil         ###   ########.fr       */
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

int	ft_playable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_check_middle(char *str, char *next)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '1')
		return (-1);
	while (str[++i])
	{
		if (ft_playable(str[i]) && ((str[i + 1] && str[i + 1] == ' ') || i == ft_strlen(str) - 1))
			return (-1);
		else if (ft_playable(str[i]) && (next[i] && (next[i] == ' ' || next[i] == '\t')))
			return (-1);
		else if (i == ft_strlen(str) - 1 && str[i] != '1')
			return (-1);
	}
	return (1);
}

int	ft_check_top_bottom(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (-1);
	}
	return (1);
}