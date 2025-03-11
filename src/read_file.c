/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:11:19 by fmorenil          #+#    #+#             */
/*   Updated: 2025/03/11 12:23:23 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ft_check_middle_line(char *str, int len)
{
	int i;
	int	space;
	
	i = 0;
	space = 1;
	while (str[i])
	{
		if (space && (str[i] != '1' && str[i] != ' '))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_first_last_line(char *str, int len)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_line(char *str, int i, int height)
{
	int len;
	
	len = ft_strlen(str) - 1;
	if (!ft_check_characters(str))
		return (0);
	if (i == 0 || i == height)
		return (ft_check_first_last_line(str, len));
	else
		return (ft_check_middle_line(str, len));	
}

static int	ft_height(char *str)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(str, O_RDONLY); 
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	return (i);
}

static t_lines	*ft_create_map(int fd, t_lines	**lines)
{
	char 	*line;
	t_lines	*tmp;
	t_lines	*last;
	
	line = get_next_line(fd);
	while (line)
	{
		tmp = malloc(sizeof(t_lines));
		if (!tmp)
			return (NULL);
		tmp->line = line;
		tmp->next = NULL;
		if (*lines == NULL)
			*lines = tmp;
		else
		{
			last = *lines;
			while (last->next)
				last = last->next;
			last->next = tmp;
		}
		line = get_next_line(fd);	
	}
	return (*lines);
}

int	ft_read_file(char *str, t_map *map)
{
	int		fd;
	int		i;
	
	map->height = ft_height(str);
	fd = open(str, O_RDONLY);
	map->lines = ft_create_map(fd, &map->lines);
	close(fd);
	i = 0;

	// if (map->lines == NULL)
	// 	printf("Map->lines: NULL\n");
	// printf("Número de filas: %i\n", map->height);
	// while (map->lines)
	// {
	// 	printf("%s", map->lines->line);
	// 	map->lines = map->lines->next;
	// }
	
	while (map->lines)
	{
		if (!ft_check_line(map->lines->line, i++, map->height))
			return (ft_print_error("Incorrect map", NULL, -1));
		map->lines = map->lines->next;
	}
	return (0);
}