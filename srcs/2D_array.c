/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:25:36 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/19 18:25:58 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		**alloc_2d_grid(int width, int height)
{
	int **grid;
	int x;
	int y;

	grid = (int **)malloc(sizeof(int *) * height);
    x = 0;
	while (x < height)
	{
		grid[x] = (int *)malloc(sizeof(int) * width);
		y = 0;
		while (y < width)
		{
			grid[x][y] = 0;
			y++;
		}
		x++;
	}
	return(grid);
}

void	free_2d_grid(int **grid, int height)
{
	int	x;

	x = 0;
	while (x < height)
	{

		free(grid[x]);
		x++;
	}
	free(grid);
}

void	print_2d_grid(int **grid, int height, int width)
{
	int x, y;

	x = 0;
	while (x < height)
	{
		y = 0;
		while (y < width)
		{
			printf("%d ", grid[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}
