/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:11:19 by fmorenil          #+#    #+#             */
/*   Updated: 2025/03/11 16:40:42 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


static int	ft_check_middle(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '1')
		return (-1);
	while (str[++i])
	{
		if (str[i] == '0' && ((str[i + 1] && str[i + 1] == ' ') || i == ft_strlen(str) - 1))
			return (-1);
	}
	return (1);
}

static int	ft_check_top_bottom(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (-1);
	}
	return (1);
}

static int	ft_check_map(t_map	*map)
{
	int	i;
	char	**lines;
	
	i = 0;
	lines = map->lines;
	while (lines[i])
	{
		if (i == 0 || i == map->height - 1)
		{
			if (ft_check_top_bottom(lines[i]) == -1)
				return (ft_print_error("Error: fila incorrecta", lines[i], 1));
		}
		else
			if (ft_check_middle(lines[i]) == -1)
				return (ft_print_error("Error: fila incorrecta ", lines[i], 1));
		i++;	
	}
	return (0);
}

static int	ft_check_lines(char	**lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!ft_check_characters(lines[i]))
			return (0);
		i++;
	}
	return (1);
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

static char	**ft_create_map(int fd, int len)
{
	char 	*line;
	char	**lines;
	int		i;
	
	line = get_next_line(fd);
	lines = malloc(sizeof(char *) * (len + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		lines[i++] = line;
		line = get_next_line(fd);	
	}
	lines[i] = NULL;
	return (lines);
}

int	ft_read_file(char *str, t_map *map)
{
	int		fd;
	
	map->height = ft_height(str);
	fd = open(str, O_RDONLY);
	map->lines = ft_create_map(fd, map->height);
	close(fd);
	int i = 0;
	while (map->lines[i])
	{
		printf("|%s|\n", map->lines[i]);
		// printf(" - First: %c\n", map->lines[i][0]);
		// printf(" - Last: %c\n", map->lines[i][ft_strlen(map->lines[i]) - 1]);
		i++;
	}
	if (!ft_check_lines(map->lines))
		return (ft_print_error("Incorrect characters map", NULL, -1));
	if (ft_check_map(map))
		return (1);
	return (0);
}
