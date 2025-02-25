/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:22:18 by fmorenil          #+#    #+#             */
/*   Updated: 2024/05/21 11:42:46 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fail_start(void)
{
	char	*array;

	array = (char *)malloc(sizeof(char) * 1);
	if (!array)
		return (NULL);
	array[0] = '\0';
	return (array);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*array;
	size_t	i;

	if ((size_t)ft_strlen((char *)s) < start)
		return (fail_start());
	if (len > (size_t)ft_strlen(s + start))
		len = (size_t)ft_strlen(s + start);
	array = ft_calloc((len + 1), sizeof(char));
	if (!array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = s[start + i];
		i++;
	}
	return (array);
}
