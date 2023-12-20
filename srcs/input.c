/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:02:48 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/20 18:03:15 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/gnl.h"

int	check_fext(char *path, char const *ext)
{
	int	i;
	int j;

	i = 0;
	if (!path[i])
		return 0;
	while(path[i++])
	{
		j = 0;
		while (path[i] && path[i] != '.')
			i++;
		while(path[i] && path[i] == ext[j++])
		{
			i++;
			if (!ext[j])
				return (1);
		}
	}
	return (0);
}

int	check_fformat(int *filein)
{
	int		len;
	int		lines;
	char	*line;

	lines = 0;
	if ((line = get_next_line(*filein)))
	{
		++lines;
		len = fdf_strlen(line);
		free(line);
		while ((line = get_next_line(*filein)))
		{
			if (fdf_strlen(line) != len)
			{
				free(line);
				return (-1);
			}
			free(line);
			++lines;
		}
	}
	return(lines);
}

int	open_file(char *argv, int *filein)
{
	if ((*filein = open(argv, O_RDONLY)) <= 0)
		return (-1);
	if (!check_fext(argv, ".fdf"))
		return (-1);
	if (check_fformat(filein) < 3)
		return (-1);
	close(*filein);
	*filein = open(argv, O_RDONLY);
	return (*filein);
}
