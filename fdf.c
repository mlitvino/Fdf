/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:14:41 by mlitvino          #+#    #+#             */
/*   Updated: 2025/01/10 16:43:01 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(int keycode, t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars ->win);
	return (0);
}
void	ft_make_gradient(int *color)
{
	unsigned char *r;
	unsigned char *g;
	unsigned char *b;

	r = (unsigned char *)color + 2;
	g = (unsigned char *)color + 1;
	b = (unsigned char *)color + 0;

	if (*r == 255 && *g < 255 && *b == 0)
		*g += 51;
	else if (*g == 255 && *r > 0 && *b == 0)
		*r -= 51;
	else if (*g == 255 && *b < 255 && *r == 0)
		*b += 51;
	else if (*b == 255 && *g > 0 && *r == 0)
		*g -= 51;
	else if (*b == 255 && *r < 255 && *g == 0)
		*r += 51;
	else if (*r == 255 && *b > 0 && *g == 0)
		*b -= 51;
}

void	printsq(t_data *img, int color, int i)
{
	int x = 1920 / 2;
	int y = 1080 / 2;

	for (int j = 0; j < i; j++)
	{
		my_mlx_pixel_put(img, x + j, y, color);
		ft_make_gradient(&color);
		my_mlx_pixel_put(img, x + i, y - j, color);
		ft_make_gradient(&color);
		my_mlx_pixel_put(img, x + i - j, y - i, color);
		ft_make_gradient(&color);
		my_mlx_pixel_put(img, x, y - i + j, color);
		ft_make_gradient(&color);
	}
}

void	draw_circle(t_data *img, int x0, int y0, int radius, int color)
{
	int x = 0;
	int y = radius;
	int d = 1 - radius; // Decision parameter

	while (x <= y)
	{
		// Symmetric points
		my_mlx_pixel_put(img, x0 + x, y0 + y, color);
		my_mlx_pixel_put(img, x0 - x, y0 + y, color);
		my_mlx_pixel_put(img, x0 + x, y0 - y, color);
		my_mlx_pixel_put(img, x0 - x, y0 - y, color);
		my_mlx_pixel_put(img, x0 + y, y0 + x, color);
		my_mlx_pixel_put(img, x0 - y, y0 + x, color);
		my_mlx_pixel_put(img, x0 + y, y0 - x, color);
		my_mlx_pixel_put(img, x0 - y, y0 - x, color);

		// Update decision parameter and points
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}

void	draw_line(t_data *img, int color, int x)
{
	int y = 300;

	while (y < 700)
	{
		my_mlx_pixel_put(img, x, y, color);
		ft_make_gradient(&color);
		y++;
	}
	if (x < 350)
		draw_line(img, 0x00FF0000, ++x);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_vars	vars;
	int		color = 0x00FF0000;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Fdf");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	//printci(&img);
	printsq(&img, color, 100);
	draw_circle(&img, 500, 500, 20, color);
	draw_line(&img, 0x00FF0000, 300);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	vars.mlx = mlx;
	vars.win = mlx_win;
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);

	mlx_loop(vars.mlx);
}
