/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:40:02 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/19 13:44:05 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		***alloc_3d_grid(int width, int height, int depth)
{
	int ***grid;
	int x;
	int y;
	int z;

	grid = (int ***)malloc(sizeof(int **) * height);
    x = 0;
	while (x < height)
	{
		grid[x] = (int **)malloc(sizeof(int *) * width);
		y = 0;
		while (y < width)
		{
			grid[x][y] = (int *)malloc(sizeof(int) * depth);
			z = 0;
			while (z < depth)
			{
				grid[x][y][z] = 0xFFFFFF;
				z++;
			}
			y++;
		}
		x++;
	}
	return(grid);
}

void	free_3d_grid(int ***grid, int height, int width)
{
	int	x;
	int	y;

	x = 0;
	while (x < height)
	{
		y = 0;
		while (y < width)
		{
			free(grid[x][y]);
			y++;
		}
		free(grid[x]);
		x++;
	}
	free(grid);
}

void	print_3d_grid(int ***grid, int height, int width, int depth)
{
	int x, y, z;

	for (z = 0; z < depth; z++)
	{
		printf("Layer %d:\n", z);
		for (x = 0; x < height; x++)
		{
			for (y = 0; y < width; y++)
			{
				printf("%d ", grid[x][y][z]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
