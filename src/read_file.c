/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:11:19 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/02 23:31:03 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ft_check_map(t_map	*map)
{
	int		i;
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
			if (ft_check_middle(lines[i], lines[i + 1]) == -1)
				return (ft_print_error("Error: fila incorrecta ", lines[i], 1));
		i++;
	}
	return (0);
}

static char	**ft_create_map(int fd, int len)
{
	char	*line;
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

static int ft_width(t_map *map)
{
    int max_width = 0;
    int i = 0;

    while (map->lines[i] != NULL)
    {
        int line_length = ft_strlen(map->lines[i]);
        if (line_length > max_width)
            max_width = line_length;
        i++;
    }
    return (max_width);
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
	close(fd);
	return (i);
}

int	ft_read_file(char *str, t_cub *cub, t_map *map)
{
	int		fd;

	map->height = ft_height(str);
	fd = open(str, O_RDONLY);
	map->lines = ft_create_map(fd, map->height);
	close(fd);
	map->width = ft_width(map);
	// int i = 0;
	// while (map->lines[i])
	// {
	// 	printf("|%s|\n", map->lines[i]);
	// 	printf(" - First: %c\n", map->lines[i][0]);
	// 	printf(" - Last: %c\n", map->lines[i][ft_strlen(map->lines[i]) - 1]);
	// 	i++;
	// }
	if (!ft_check_lines(map->lines))
		return (-1);
	ft_find_player(map->lines, &cub->player);
	ft_init_player(&cub->player);
	// printf("Player: %c\n", cub->player.orientation);
	// printf("Player x: %f\n", cub->player.x_coord);
	// printf("Player y: %f\n", cub->player.y_coord);
	// printf("Player x plane: %f\n", cub->player.x_plane);
	// printf("Player y plane: %f\n", cub->player.y_plane);
	if (ft_check_map(map))
		return (1);
	return (0);
}
