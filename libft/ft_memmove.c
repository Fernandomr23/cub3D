/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:18:13 by fmorenil          #+#    #+#             */
/*   Updated: 2024/03/19 16:35:33 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*str;

	str = dst;
	if (!dst && !src)
		return (0);
	if (src < dst)
	{
		src += len;
		dst += len;
		while (len--)
		{
			*(char *)--dst = *(char *)--src;
		}
	}
	else
		while (len--)
			*(char *)dst++ = *(char *)src++;
	return (str);
}
