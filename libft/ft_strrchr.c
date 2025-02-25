/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:57:22 by fmorenil          #+#    #+#             */
/*   Updated: 2024/03/22 12:11:04 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen((char *)s);
	while (len > 0 && s[len] != (char)c)
	{
		len--;
	}
	if (s[len] == (char)c || !c)
		return ((char *)s + len);
	return (NULL);
}
