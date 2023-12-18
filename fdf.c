/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/18 18:25:02 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(char *argv, int *filein)
{
	if ((*filein = open(argv, O_RDONLY)) <= 0)
		return (-1);
	return (*filein);
}

int	main(int argc, char **argv)
{
	int filein;
	char buf[256];
	int  cread;

	if (argc == 2)
	{
		open_file(argv[1], &filein);
		while ((cread = read(filein, buf, 10)))
		{
			printf("%s\n", buf);
		}

	}
	close(filein);
	return(0);
}

