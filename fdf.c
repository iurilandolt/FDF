/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/21 16:51:52 by rlandolt         ###   ########.fr       */
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
	//free_2d_grid(instance->source, instance->height);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
			my_mlx_pixel_put(data, x_center, y_center, color);
		}
	}
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
			instance->mlx_ser = mlx_init();
			instance->mlx_win = mlx_new_window(instance->mlx_ser, W_WIDTH,W_HEIGHT, "fml");
			instance->mlx_img.img= mlx_new_image(instance->mlx_ser, W_WIDTH, W_HEIGHT);
			instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img, &instance->mlx_img.bits_per_pixel,
													&instance->mlx_img.line_length, &instance->mlx_img.endian);

			draw_array_points(&instance->mlx_img, instance->source, instance->height, instance->width);
			mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
			mlx_loop(instance->mlx_ser);
		}
		free(instance);
		close(filein);
		printf("\n");
	}
	return(0);
}

