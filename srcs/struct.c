/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:53:52 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 17:12:22 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/gnl.h"
#include "../.minilibx/mlx.h"

void	build_t_point_grid(t_session *instance, int filein)
{
	char		*line;
	char		**tab;
	char		**color;
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
			color = ft_split(tab[i.x], ',');
			instance->source[i.y][i.x].y = i.y;
			instance->source[i.y][i.x].x = i.x;
			instance->source[i.y][i.x].z = ft_atoi(tab[i.x]);
			if (color[1])
				instance->source[i.y][i.x].c = ft_atohex(color[1]);
			clear(color);
			i.x++;
		}
		clear(tab);
		free(line);
		i.y++;
	}
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


//debug functions, remove before submitting
void	print_t_points(t_point **grid, int height, int width)
{
	int y, x;
	if (!grid || !*grid)
		return ;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("%-3d ", grid[y][x].z);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}


void print_t_points_info(t_point **grid, int height, int width) {
    printf("Grid Points (x, y, z):\n");
    printf("----------------------------------------\n");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("| (%3d, %3d, %3d) ", grid[y][x].x, grid[y][x].y, grid[y][x].z);
            // printf("| Color: %s ", grid[y][x].c);
        }
        printf("|\n");
        printf("----------------------------------------\n");
    }
    printf("\n");
}
