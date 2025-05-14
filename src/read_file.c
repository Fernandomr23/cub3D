/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:11:19 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/14 17:40:39 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ft_check_map(t_map	*map)
{
	int		i;
	char	**lines;

	i = 0;
	lines = map->lines;
	while (i < map->height)
	{
		if (i == 0 || i == map->height - 1)
		{
			if (ft_check_top_bottom(lines[i]) == -1)
				return (ft_print_error("Error: incorrect file ", lines[i], 1));
		}
		else
			if (ft_check_middle(lines[i], lines[i + 1], lines[i - 1]) == -1)
				return (ft_print_error("Error: incorrect file ", lines[i], 1));
		i++;
	}
	return (0);
}

static int	ft_create_map(t_cub *cub, int fd, int in_map)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	printf("Height: %d\n", cub->map->height);
	while (line && i < cub->map->height)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (in_map == 0 && ft_map_line(line))
			in_map = 1;
		if (in_map)
			cub->map->lines[i++] = ft_strdup(line);
		else
		{
			if (ft_store_texture(cub, line) == -1)
				return (ft_print_error("Error: invalid texture", line, 1));
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("Numer of lines: %d\n", i);
	cub->map->lines[i] = NULL;
	return (0);
}

static int	ft_map_width(t_map *map)
{
	int	max_width;
	int	i;
	int	line_length;

	max_width = 0;
	i = 0;
	while (map->lines[i] != NULL)
	{
		line_length = ft_strlen(map->lines[i]);
		if (line_length > max_width)
			max_width = line_length;
		i++;
	}
	return (max_width);
}

static int	ft_map_height(char *str)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (ft_map_line(line))
			i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

int	ft_read_file(char *str, t_cub *cub, t_map *map)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		exit(ft_print_error("Error opening file", str, 1));
	map->height = ft_map_height(str);
	cub->map->lines = malloc(sizeof(char *) * (map->height + 1));
	if (!cub->map->lines)
		return (ft_print_error("Error: malloc", NULL, 1));
	ft_create_map(cub, fd, 0);
	map->width = ft_map_width(map);
	close(fd);
	if (!ft_check_lines(map->lines))
		return (1);
	ft_find_player(map->lines, &cub->player);
	ft_init_player(&cub->player);
	if (ft_check_map(map))
		return (1);
	return (0);
}
