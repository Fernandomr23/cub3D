/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:46:05 by fmorenil          #+#    #+#             */
/*   Updated: 2024/05/21 11:41:54 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	array = (void *)malloc((count * size));
	if (!array)
		return (NULL);
	ft_bzero(array, count * size);
	return (array);
}
