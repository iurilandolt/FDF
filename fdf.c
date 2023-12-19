/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/19 19:18:32 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include "include/gnl.h"

int	open_file(char *argv, int *filein)
{
	if ((*filein = open(argv, O_RDONLY)) <= 0)
		return (-1);
	return (*filein);
}


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


int	check_format(char *argv, int *filein)
{
	int		len_control;
	int		len;
	int		lines;
	char	*line;

	if (open_file(argv[1], &filein) > 0)
	{
		lines = 0;
		if (line = get_next_line(filein))
		{
			lines++;
			len_control = ft_strlen(line);
			free(line);
			while ((line = get_next_line(filein)))
			{
				len = ft_strlen(line);
				free(line);
				if (len != len_control)
				{
					close(&filein);
					return(-1);
				}
				lines++;
			}
			close(&filein);
			return(lines);
		}
	}
	return (0);
}


int	main(int argc, char **argv)
{
	int filein;
	char *line;

	if (argc == 2)
	{
		if (!check_fext(argv[1], ".fdf"))
			return (0);
		if (open_file(argv[1], &filein) > 0)
		{
			while ((line = get_next_line(filein)))
			{
				printf("%s", line);
				free(line);
			}
			printf("\n");
		}
	}
	close(filein);
	return(0);
}

