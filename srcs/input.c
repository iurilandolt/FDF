/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:02:48 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 15:13:26 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/gnl.h"


int	check_fext(char *path, char const *ext)
{
	t_vector2 i;

	i.x = 0;
	if (!path[i.x])
		return 0;
	while(path[i.x++])
	{
		i.y = 0;
		while (path[i.x] && path[i.x] != '.')
			i.x++;
		while(path[i.x] && path[i.x] == ext[i.y++])
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
	t_vector2 colums;

	colums.x = 0;
	colums.y = 0;
	while (str[colums.x])
	{
		while(str[colums.x] == 32)
			colums.x++;
		if (str[colums.x] && str[colums.x] != 32)
		{
			colums.x++;
			colums.y++;
		}
		while(str[colums.x] && str[colums.x] != 32)
			colums.x++;
	}
	return (colums.y);
}

int	check_fformat(t_session *instance, int filein)
{
	int		len;
	int		lines;
	char	*line;

	lines = 0;
	if ((line = get_next_line(filein)))
	{
		++lines;
		len = check_width(line);
		free(line);
		while ((line = get_next_line(filein)))
		{
			if (check_width(line) == len)
			{
				free(line);
				++lines;
			}
			else
			{
				free(line);
				break;
			}
		}
	}
	instance->height = lines;
	instance->width = 0;
	return(lines);
}
//set errno = 0, use perror to printf error message?
int	open_file(t_session *instance, char *argv)
{
	int filein;

	if ((filein = open(argv, O_RDONLY)) <= 0)
	{
		printf("Error\nCould not open file %s\n", argv);
		return (-1);
	}
	if (!check_fext(argv, ".fdf"))
	{
		printf("Error\nFile %s is not a .fdf file\n", argv);
		return (-1);
	}
	if (check_fformat(instance, filein) < 3)
	{
		printf("Error\nFile %s is not a valid .fdf file\n", argv);
		return (-1);
	}
	close(filein);
	filein = open(argv, O_RDONLY);
	return (filein);
}
