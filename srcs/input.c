/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:02:48 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/27 22:19:26 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/gnl.h"

int	check_fext(char *path, char const *ext)
{
	t_vector2	i;

	i.x = 0;
	if (!path[i.x])
		return (0);
	while (path[i.x++])
	{
		i.y = 0;
		while (path[i.x] && path[i.x] != '.')
			i.x++;
		while (path[i.x] && path[i.x] == ext[i.y++])
		{
			i.x++;
			if (!ext[i.y])
				return (1);
		}
	}
	return (0);
}

int	check_width(char *str)
{
	t_vector2	colums;

	colums.x = 0;
	colums.y = 0;
	while (str[colums.x])
	{
		while (str[colums.x] == 32)
			colums.x++;
		if (str[colums.x] && str[colums.x] != 32)
		{
			colums.x++;
			colums.y++;
		}
		while (str[colums.x] && str[colums.x] != 32)
			colums.x++;
	}
	return (colums.y);
}

int	check_fformat(t_session *instance, int filein)
{
	t_vector2	i;
	char		*line;

	i.y = 0;
	if ((line = get_next_line(filein)))
	{
		++i.y;
		i.x = check_width(line);
		free(line);
		while ((line = get_next_line(filein)))
		{
			if (check_width(line) != i.x)
			{
				free(line);
				break ;
			}
			else
				++i.y;
			free(line);
		}
	}
	instance->height = i.y;
	instance->width = 0;
	return (i.y);
}

int	open_file(t_session *instance, char *argv)
{
	int	filein;

	if ((filein = open(argv, O_RDONLY)) <= 0)
	{
		perror("42/FDF -> Error\nCould not open file\n");
		return (-1);
	}
	if (!check_fext(argv, ".fdf"))
	{
		errno = 1;
		perror("42/FDF -> Error\nFile is not a .fdf file\n");
		return (-1);
	}
	if (check_fformat(instance, filein) < 3)
	{
		errno = 1;
		perror("42/FDF -> Error\nNot a valid .fdf file\n");
		return (-1);
	}
	close(filein);
	filein = open(argv, O_RDONLY);
	return (filein);
}
