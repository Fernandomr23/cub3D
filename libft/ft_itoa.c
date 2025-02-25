/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:02:42 by fmorenil          #+#    #+#             */
/*   Updated: 2024/03/20 16:54:06 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countdigits(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		digits;
	long int	num;

	digits = ft_countdigits(n);
	num = n;
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	str = (char *)malloc((digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	*(str + digits) = 0;
	while (digits > 0)
	{
		*(str + digits - 1) = num % 10 + '0';
		num = num / 10;
		digits--;
	}
	if (n < 0)
		*(str + digits) = '-';
	return (str);
}
