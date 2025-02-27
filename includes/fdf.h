/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:14:50 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/26 13:05:14 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define ZOOM_FACTOR 1.1
# define TRANS_FACTOR 10
# define ALTITUDE 0.025

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101

# define DESTROY_NOTIFY 17
# define BUTTON_PRESS 4
# define KEY_PRESS 2
# define KEY_PRESS_MASK 1L

typedef struct s_3dpoint
{
	int	x;
	int	y;
	int	z;
}	t_3dpoint;

typedef struct s_2dpoint
{
	double	x;
	double	y;
	double	h;
	int		color;
}	t_2dpoint;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		gradient;
	double	t;
}	t_color;

typedef struct s_delta
{
	double	dx;
	double	dy;
}	t_delta;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;

	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			updating;

	double		alpha;
	double		scale;
	double		altitude;
	double		translt_x;
	double		translt_y;

	int			map_w;
	int			map_h;
	int			min_h;
	int			max_h;

	t_3dpoint	*file_map;
	t_2dpoint	*scr_map;
}	t_data;

// checks.c
void	check_file_name(char *file);
int		check_inval_ch(char *line);
int		check_form(char *line, t_data *data);
void	check_map(char *file, t_data *data);

// draw.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	create_lines(t_data *data);
void	draw_line(t_data *data, t_2dpoint p0, t_2dpoint p1);

// get_map.c
int		split_line(char *line, int *temp_map, int i, int max_points);
int		*get_points(t_data *data, char *file);
void	get_map(char *file, t_data *data);

// hooks.c
int		close_win(t_data *data);
int		mouse_handler(int mousecode, int x, int y, t_data *data);
int		key_handler(int key, t_data *data);
void	init_hooks(t_data *data);
int		render(t_data *data);

// inits.c
void	check_mlx_init(void *ptr, t_data *data, char *message);
void	init_screen_map(t_data *data);
void	init_data(t_data *data);
int		init_mlx(t_data *data);

// utils.c
int		count_word(char *line);
void	print_err(char	*error);
int		ft_strcmp(const char *s1, const char *s2);

#endif
