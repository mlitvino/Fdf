/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:17:38 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/26 14:54:35 by mlitvino         ###   ########.fr       */
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
	ft_putendl_fd(error, 2);
	exit (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
