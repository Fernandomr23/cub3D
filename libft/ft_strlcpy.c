/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:01:23 by fmorenil          #+#    #+#             */
/*   Updated: 2024/03/22 10:37:20 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	value;

	i = 0;
	value = ft_strlen((char *)src);
	if (size == 0)
		return (value);
	while (src[i] != '\0' && (size - 1) > 0)
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	dst[i] = '\0';
	return (value);
}
