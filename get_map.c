/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:00:35 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/18 17:36:29 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	split_line(char *line, int *temp_map, int i, int max_points)
{
	char	**values;
	int		x;

	values = ft_split(line, ' ');
	if (!values)
		return (free(temp_map), -1);
	x = 0;
	while (values[x] && i < max_points)
	{
		temp_map[i] = ft_atoi(values[x]);
		free(values[x]);
		x++;
		i++;
	}
	free(values);
	return (i);
}

int	*get_points(t_data *data, char *file)
{
	int		fd;
	int		i;
	int		max_points;
	char	*line;
	int		*temp_map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	max_points = data->map_h * data->map_w;
	temp_map = malloc(max_points * sizeof(int));
	if (!temp_map)
		return (close(fd), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = split_line(line, temp_map, i, max_points);
		if (i == -1)
			(free(line), print_err("Error: Malloc failed"));
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), temp_map);
}

void	get_map(char *file, t_data *data)
{
	int			i;
	int			*temp_map;
	t_3dpoint	temp;

	i = 0;
	data->file_map = malloc(data->map_h * data->map_w * sizeof(t_3dpoint));
	if (!data->file_map)
		print_err("Error: malloc failed");
	temp_map = get_points(data, file);
	if (!temp_map)
		(free(data->file_map), print_err("Error: file_map parsing failed"));
	temp.y = 0;
	while (temp.y < data->map_h)
	{
		temp.x = 0;
		while (temp.x < data->map_w)
		{
			temp.z = temp.y * data->map_w + temp.x;
			data->file_map[temp.z] = (t_3dpoint){temp.x, temp.y, temp_map[i]};
			i++;
			temp.x++;
		}
		temp.y++;
	}
	free(temp_map);
}
