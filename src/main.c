/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:38 by fmorenil          #+#    #+#             */
/*   Updated: 2025/04/03 21:41:45 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static t_map	*ft_init_map(void) {
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (NULL);
	return (map);
}

static t_cub	*ft_init(char *str)
{
	t_cub	*data;

	data = (t_cub *)malloc(sizeof(t_cub));
	data->title = ft_strjoin("Cub3D - ", str);
	if (!data)
		return (ft_print_error("Malloc error", NULL, 1), NULL);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_print_error("Connection error", NULL, 1), NULL);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, data->title);
	if (!data->win)
		return (ft_print_error("Window error", NULL, 1), NULL);
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	if (!data->img)
		return (ft_print_error("Image error", NULL, 1), NULL);
	data->data_addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->size_line, &data->endian);
	data->map = ft_init_map();
	return (data);
}

static int	ft_check_args(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + (len - 4), ".cub", 4) || len <= 4)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*data;

	if (argc != 2)
		return (ft_print_error("Incorrect number of args", NULL, 1));
	if (ft_check_args(argv[1]))
		return (ft_print_error("Incorrect file extension:", argv[1], 1));
	data = ft_init(argv[1]);
	if (ft_read_file(argv[1], data->map))
		return (-1);
	ft_controls(data);
	// ft_draw(data);
	mlx_loop(data->mlx);
}
