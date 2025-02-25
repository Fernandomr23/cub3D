/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:13:11 by fmorenil          #+#    #+#             */
/*   Updated: 2024/07/29 14:16:21 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_table(char **array, int i)
{
	while (i > 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
	return (NULL);
}

static size_t	ft_countstr(char const *s, char c)
{
	size_t	i;
	size_t	word;
	size_t	count;

	i = 0;
	word = 1;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			word = 1;
		else if (word == 1)
		{
			word = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static int	ft_splitwords(char **array, char const *s, char c, int word)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (s[end])
	{
		if (s[end] == c || s[end] == 0)
			start = end + 1;
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == 0))
		{
			array[word] = malloc(((end - start) + 2) * sizeof(char));
			if (!array[word])
				return (0);
			ft_strlcpy(array[word], (s + start), (end - start) + 2);
			word++;
		}
		end++;
	}
	array[word] = NULL;
	return (1);
}

char	**ft_split(char *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_countstr(s, c);
	array = (char **)malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!ft_splitwords(array, s, c, 0))
		return (ft_free_table(array, words));
	return (array);
}
