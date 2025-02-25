/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:38 by fmorenil          #+#    #+#             */
/*   Updated: 2025/02/25 10:01:55 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static t_cub	*ft_init(char *str)
{
	char	*title;
	t_cub	*data;

	title = ft_strjoin("Cub3D - ", str);
	data = (t_cub *)malloc(sizeof(t_cub));
	if (!data)
		return (ft_print_error("Malloc error", NULL, 1), NULL);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_print_error("Connection error", NULL, 1), NULL);
	data->win = mlx_new_window(data->mlx, 1920, 1080, title);
	if (!data->win)
		return (ft_print_error("Window error", NULL, 1), NULL);
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	if (!data->img)
		return (ft_print_error("Image error", NULL, 1), NULL);
	data->data_addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->size_line, &data->endian);
	return (data);
}

int	main(int argc, char **argv)
{
	char	*file;
	t_cub	*data;
	int		len;

	if (argc != 2)
		return (ft_print_error("Incorrect number of args", NULL, 1));
	file = argv[1];
	len = ft_strlen(file);
	if (ft_strncmp(file + (len - 4), ".cub", 4) || len <= 4)
		return (ft_print_error("Incorrect file extension:", file, 1));
	data = ft_init(file);
	mlx_loop(data->mlx);
}
