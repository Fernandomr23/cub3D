/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:42 by fmorenil          #+#    #+#             */
/*   Updated: 2024/05/21 11:46:16 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*array;

	len = ft_strlen((char *)s1) + 1;
	array = (char *)malloc(len * sizeof(char));
	if (!array)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		array[i] = s1[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}
