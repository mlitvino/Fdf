/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:17:38 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/11 18:18:09 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_word(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] != '\n' && line[i] == ' ')
			i++;
		if (line[i] && line[i] != '\n')
		{
			count++;
			while (line[i] && line[i] != '\n' && line[i] != ' ')
				i++;
		}
	}
	return (count);
}

void	print_err(char	*error)
{
	ft_printf("%s\n", error);
	exit (1);
}
