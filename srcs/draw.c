/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/22 12:33:10 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

//draw_circle(&instance->mlx_img, WIDTH / 2, HEIGHT /2, 500, 0x00FF0000);
void draw_circle(t_data *data, int cx, int cy, int radius, int color)
{
	for (int y = cy - radius; y <= cy + radius; ++y)
	{
		for (int x = cx - radius; x <= cx + radius; ++x)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius)
			{
				my_mlx_pixel_put(data, x, y, color);
			}
		}
	}
}

void draw_rectangle(t_data *data, int height, int width, int color)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}

void draw_array_cells(t_data *data, int **array, int rows, int cols)
{
	int width = W_WIDTH / cols;   // Calculate width of each rectangle
	int height = W_HEIGHT / rows; // Calculate height of each rectangle

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < cols; ++x)
		{
			int color = array[y][x] * 10;
			int startX = x * width;
			int startY = y * height;

			// Draw a point for each cell // d stands for displacement
			for (int dy = 0; dy < height; ++dy)
			{
				for (int dx = 0; dx < width; ++dx)
				{
					my_mlx_pixel_put(data, startX + dx, startY + dy, color);
				}
			}
		}
	}
}

void draw_array_points(t_data *data, int **array, int rows, int cols)
{
	// Calculate the size of each square
	int dx = W_WIDTH / cols;
	int dy = W_HEIGHT / rows;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int color = array[i][j] * 25;
			int x_center = j * dx + dx / 2; // Calculate the center x-coordinate
			int y_center = i * dy + dy / 2; // Calculate the center y-coordinate

			// Draw a single point for each cell
			my_mlx_pixel_put(data, y_center, x_center, color);
		}
	}
}
