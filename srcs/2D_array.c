/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:25:36 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/22 15:11:30 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		**alloc_2d_grid(int width, int height)
{
	int **grid;
	int y;
	int x;

	grid = (int **)malloc(sizeof(int *) * height);
    y = 0;
	while (y < height)
	{
		grid[y] = (int *)malloc(sizeof(int) * width);
		x = 0;
		while (x < width)
		{
			grid[y][x] = 0;
			x++;
		}
		y++;
	}
	return(grid);
}

void	free_2d_grid(int **grid, int height)
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

void	print_2d_grid(int **grid, int height, int width)
{
	int y, x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("%-3d ", grid[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}
