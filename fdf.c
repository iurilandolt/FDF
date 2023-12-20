/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/20 19:50:05 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include "include/gnl.h"

void	gen_source(t_session *instance, int filein)
{
	char	*line;
	//char	**tab;

	instance->source = alloc_2d_grid(0, 0); // alloc height
	free_2d_grid(instance->source, 0);
	while ((line = get_next_line(filein)))
	{
		printf("%s", line);
		free(line);
	}
}

int	main(int argc, char **argv)
{
	int			filein;
	t_session	*instance;

	if (argc == 2)
	{
		instance = (t_session *)malloc(sizeof(t_session *));
		if (!instance)
			return (0);
		filein = open_file(argv[1]);
		if (filein > 2)
		{
			gen_source(instance, filein);
		}
		printf("\n");
	}
	free(instance);
	close(filein);
	return(0);
}


// use gen source function similar to open file ? close fd after
// fd is in struct ?


/*
int	main(int argc, char **argv)
{
	int		filein;
	char	*line;

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
		printf("\n");
	}
	close(filein);
	return(0);
}

*/
