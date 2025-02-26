/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:14:41 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/26 17:39:49 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		print_err("Error: Wrong input format");
	check_file_name(argv[1]);
	init_data(&data);
	check_map(argv[1], &data);
	get_map(argv[1], &data);
	init_mlx(&data);
	return (0);
}
