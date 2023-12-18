/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/18 21:12:57 by rlandolt         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int filein;
	char *line;

	if (argc == 2)
	{
		if (open_file(argv[1], &filein) > 0)
		{
			while ((line = get_next_line(filein)))
			{
				printf("%s", line);
				free(line);
			}
		}
	}
	close(filein);
	return(0);
}

