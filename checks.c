/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:05:09 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/16 19:05:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_file_name(char *file)
{
	char	*dot;

	if (!file)
		print_err("Error: No such file");
	dot = ft_strrchr(file, '.');
	if (!dot || dot[1] == '\0' || ft_strcmp(dot, ".fdf") != 0)
		print_err("Error: Wrong file format");
}

int	check_inval_ch(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != '-'
			&& line[i] != ' ' && line[i] != '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_form(char *line, t_data *data)
{
	if (data->map_h == 0)
		data->map_w = count_word(line);
	else
	{
		if (data->map_w != count_word(line))
		{
			return (1);
		}
	}
	data->map_h++;
	return (0);
}

void	check_map(char *file, t_data *data)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_err("Error: unable to open file");
	line = get_next_line(fd);
	if (!line)
		(close(fd), print_err("Error: file is empty"));
	while (line)
	{
		if (check_inval_ch(line) == 1 || check_form(line, data) == 1)
		{
			free(line);
			close(fd);
			print_err("Error: Invalid character in file");
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
