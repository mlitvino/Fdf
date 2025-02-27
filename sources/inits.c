/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:30:15 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/27 13:42:50 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_mlx_init(void *ptr, t_data *data, char *message)
{
	if (!ptr)
	{
		free(data->file_map);
		print_err(message);
	}
}

void	init_data(t_data *data)
{
	data->win_w = WIN_WIDTH;
	data->win_h = WIN_HEIGHT;
	data->map_h = 0;
	data->map_w = 0;
	data->min_h = -1;
	data->max_h = 1;
	data->alpha = 0.7;
	data->translt_x = -100;
	data->translt_y = -200;
	data->scale = 30;
	data->altitude = 1;
	data->updating = 1;
	data->scr_map = NULL;
	data->file_map = NULL;
}

int	get_color(t_data *data, double z)
{
	double	ratio;
	t_color	color;

	if (z > data->max_h)
		data->max_h = z;
	if (z < data->min_h)
		data->min_h = z;
	ratio = (z - data->min_h) / (data->max_h - data->min_h);
	if (ratio < 0.0)
		ratio = 0.0;
	if (ratio > 1.0)
		ratio = 1.0;
	color.r = (int)(255 * ratio);
	color.g = 0;
	color.b = (int)(255 * (1.0 - ratio));
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	init_screen_map(t_data *data)
{
	int		i;
	double	x;
	double	y;
	double	z;

	data->scr_map = malloc(data->map_h * data->map_w * sizeof(t_2dpoint));
	if (!data->scr_map)
		(free(data->file_map), print_err("Error: Malloc failed"));
	i = 0;
	while (i < data->map_h * data->map_w)
	{
		x = data->file_map[i].x;
		y = data->file_map[i].y;
		z = data->file_map[i].z * data->altitude;
		data->scr_map[i].x = (x - y) * cos(data->alpha);
		data->scr_map[i].y = (x + y) * sin(data->alpha) - z;
		data->scr_map[i].x *= data->scale;
		data->scr_map[i].y *= data->scale;
		data->scr_map[i].x += (data->win_w / 2) + data->translt_x;
		data->scr_map[i].y += (data->win_h / 2) + data->translt_y;
		data->scr_map[i].h = z;
		data->scr_map[i].color = get_color(data, z);
		i++;
	}
}

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	check_mlx_init(data->mlx, data, "Error: mlx failed");
	data->win = mlx_new_window(data->mlx, data->win_w, data->win_h, "Fdf");
	check_mlx_init(data->win, data, "Error: win failed");
	data->img = mlx_new_image(data->mlx, data->win_w, data->win_h);
	check_mlx_init(data->img, data, "Error: img failed");
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	init_screen_map(data);
	create_lines(data);
	init_hooks(data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	return (0);
}
