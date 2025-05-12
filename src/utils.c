/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:00:33 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/12 17:21:14 by fmorenil         ###   ########.fr       */
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

int	ft_map_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			return (1);
		else if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);
	}
	return (0);
}

static int	ft_calculate_len(char *str, int *i)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	while (str[(*i)] == ' ' || str[(*i)] == '\t')
		(*i)++;
	return (len);
}

int	ft_check_middle(char *str, char *next, char *prev)
{
	int	i;
	int	len;

	i = 0;
	len = ft_calculate_len(str, &i);
	if (str[i] != '1')
		return (-1);
	while (i < len)
	{
		if (ft_playable(str[i]))
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0')
				return (-1);
			if (!next[i] || next[i] == ' ' || next[i] == '\t')
				return (-1);
			if (!prev[i] || prev[i] == ' ' || prev[i] == '\t')
				return (-1);
		}
		else if (str[i] == '\0')
			break ;
		i++;
	}
	if (str[len - 1] != '1')
		return (-1);
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
