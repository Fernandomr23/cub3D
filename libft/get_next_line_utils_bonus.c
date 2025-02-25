/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:42:41 by fmorenil          #+#    #+#             */
/*   Updated: 2024/07/29 12:33:06 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	while (last && last->next)
		last = last->next;
	return (last);
}

int	ft_newline(t_list *list)
{
	int		i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	generate_line(t_list *list, char *next_line)
{
	int	i;
	int	len;

	if (list == NULL)
		return ;
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				next_line[len++] = '\n';
				next_line[len] = '\0';
				return ;
			}
			next_line[len++] = list->str_buf[i++];
		}
		list = list->next;
	}
	next_line[len] = '\0';
}

int	ft_strlen_to_nl(t_list *list)
{
	int		i;
	int		len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	free_list(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*next;

	if (*list == NULL)
		return ;
	while (*list)
	{
		next = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = next;
	}
	*list = NULL;
	if (clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
