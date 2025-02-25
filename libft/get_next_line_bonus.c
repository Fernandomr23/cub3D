/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:41:21 by fmorenil          #+#    #+#             */
/*   Updated: 2024/07/29 12:32:44 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	char	*buf;
	int		i;
	int		j;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (clean_node == NULL || buf == NULL)
		return ;
	last_node = ft_lstlast(*list);
	i = 0;
	j = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[j++] = last_node->str_buf[i];
	buf[j] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	free_list(list, clean_node, buf);
}

char	*get_line(t_list *list)
{
	char	*next_line;
	int		len;

	if (list == NULL)
		return (NULL);
	len = ft_strlen_to_nl(list);
	next_line = (char *)malloc(len + 1);
	if (next_line == NULL)
		return (NULL);
	generate_line(list, next_line);
	return (next_line);
}

void	to_the_list(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->str_buf = buf;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		last_node = ft_lstlast(*list);
		last_node->next = new_node;
	}
}

int	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!ft_newline(*list))
	{
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (-1);
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == -1)
		{
			free(buf);
			return (-1);
		}
		if (char_read == 0)
		{
			free(buf);
			return (0);
		}
		buf[char_read] = '\0';
		to_the_list(list, buf);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*next_line;
	t_list			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (create_list(&list[fd], fd) == -1)
	{
		while (list[fd])
		{
			tmp = (list[fd])->next;
			free((list[fd])->str_buf);
			free(list[fd]);
			list[fd] = tmp;
		}
		list[fd] = NULL;
	}
	if (list[fd] == NULL)
		return (NULL);
	next_line = get_line(list[fd]);
	clean_list(&list[fd]);
	return (next_line);
}
