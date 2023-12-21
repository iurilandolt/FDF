/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/21 13:51:54 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include "include/gnl.h"
#include ".minilibx/mlx.h"

void	gen_source(t_session *instance, int filein)
{
	char		*line;
	char		**tab;
	t_vector2	i;

	i.x = 0;
	instance->source = (int**)malloc(sizeof(int *) * instance->height);
	while ((line = get_next_line(filein)) && i.x < instance->height)
	{
		i.y = 0;
		tab = ft_split(line, ' ');
		instance->width = tab_size(tab);
		instance->source[i.x] =  (int *)malloc(sizeof(int) * instance->width);
		while (tab[i.y] && i.y < instance->width)
		{
			instance->source[i.x][i.y] = ft_atoi(tab[i.y]);
			printf("%-3d ", instance->source[i.x][i.y]);
			i.y++;
		}
		printf("\n");
		clear(tab);
		free(line);
		i.x++;
	}
	free_2d_grid(instance->source, instance->height);
}

int	main(int argc, char **argv)
{
	int			filein;
	t_session	*instance;

	if (argc == 2)
	{
		instance = (t_session *)malloc(sizeof(t_session));
		if (!instance)
			return (0);
		filein = open_file(instance, argv[1]);
		if (filein > 2)
		{
			gen_source(instance, filein);
		}
		instance->mlx_ser = mlx_init();
		instance->mlx_win = mlx_new_window(instance->mlx_ser, WIDTH, HEIGHT, "Untitled Window");
		mlx_loop(instance->mlx_ser);
		free(instance);
		close(filein);
		printf("\n");
	}
	return(0);
}

