/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:44:54 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/26 14:53:09 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_win(t_data *data)
{
	free(data->scr_map);
	free(data->file_map);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	exit (0);
}

int	mouse_handler(int mousecode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (mousecode == 4)
		data->scale *= ZOOM_FACTOR;
	else if (mousecode == 5)
		data->scale /= ZOOM_FACTOR;
	data->updating = 1;
	return (0);
}

int	key_handler(int key, t_data *data)
{
	if (key == KEY_ESC)
		close_win(data);
	else if (key == KEY_W)
		data->translt_y -= TRANS_FACTOR;
	else if (key == KEY_S)
		data->translt_y += TRANS_FACTOR;
	else if (key == KEY_A)
		data->translt_x -= TRANS_FACTOR;
	else if (key == KEY_D)
		data->translt_x += TRANS_FACTOR;
	else if (key == KEY_Q)
		data->altitude += ALTITUDE;
	else if (key == KEY_E)
		data->altitude -= ALTITUDE;
	data->updating = 1;
	return (0);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data->win, DESTROY_NOTIFY, 0, close_win, data);
	mlx_hook(data->win, BUTTON_PRESS, 1L << 2, mouse_handler, data);
	mlx_hook(data->win, KEY_PRESS, KEY_PRESS_MASK, key_handler, data);
}

int	render(t_data *data)
{
	if (data->updating == 1)
	{
		ft_bzero(data->addr, data->win_h * data->line_length);
		free(data->scr_map);
		init_screen_map(data);
		create_lines(data);
		data->updating = 0;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
