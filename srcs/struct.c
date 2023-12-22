/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:53:52 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/22 18:15:10 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/gnl.h"
#include "../.minilibx/mlx.h"

void	gen_t_points(t_session *instance, int filein)
{
	char		*line;
	char		**tab;
	t_vector2	i;

	i.y = 0;
	instance->source = (t_point**)malloc(sizeof(t_point *) * instance->height);
	while ((line = get_next_line(filein)) && i.y < instance->height)
	{
		i.x = 0;
		tab = ft_split(line, ' ');
		instance->width = tab_size(tab);
		instance->source[i.y] =  (t_point *)malloc(sizeof(t_point) * instance->width);
		while (tab[i.x] && i.x < instance->width)
		{
			instance->source[i.y][i.x].y = i.y;
			instance->source[i.y][i.x].x = i.x;
			instance->source[i.y][i.x].z = ft_atoi(tab[i.x]);
			ft_strlcpy(instance->source[i.y][i.x].c, "0x000000", 8);
			i.x++;
		}
		clear(tab);
		free(line);
		i.y++;
	}
	print_t_points(instance->source, instance->height, instance->width);
}

void	print_t_points(t_point **grid, int height, int width)
{
	int y, x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("%-3d ", grid[y][x].z);
			//printf(" : %s", grid[y][x].c);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}

void	free_t_points(t_point **grid, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{

		free(grid[y]);
		y++;
	}
	free(grid);
}