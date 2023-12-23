/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/23 16:02:41 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include ".minilibx/mlx.h"

void	isometric_transform(t_session *instance)
{
	t_transform	new;
	t_vector2	i;
	t_vector3	d;


	instance->projection = (t_point**)malloc(sizeof(t_point *) * instance->height);
	new.angle = 30.0;
	new.radian_angle = new.angle * M_PI / 180.0;
	new.z_scale = 0.5;
	i.y = 0;
	while (i.y < instance->height)
	{
		i.x = 0;
		instance->projection[i.y] =  (t_point *)malloc(sizeof(t_point) * instance->width);
		while (i.x < instance->width)
		{
			d.y = (float)instance->source[i.y][i.x].y;
			d.x = (float)instance->source[i.y][i.x].x;
			d.z = (float)instance->source[i.y][i.x].z * new.z_scale;


			instance->projection[i.y][i.x].y = (d.x + d.y) * sin(new.radian_angle) - d.z;
			instance->projection[i.y][i.x].x = (d.x - d.y) * cos(new.radian_angle);
			instance->projection[i.y][i.x].z = instance->source[i.y][i.x].z;

			i.x++;
		}
		i.y++;
	}
	printf("Projection\n");
	print_t_points_info(instance->projection, instance->height, instance->width);
}

void convert_points(t_point **src, int rows, int cols)
{
	float aspect_ratio = (float)W_WIDTH / W_HEIGHT;
	float grid_aspect_ratio = (float)(cols - 1) / (rows - 1);

	float d_x, d_y;
	if (grid_aspect_ratio > aspect_ratio)
	{
		// Window is taller than grid aspect ratio, so fit to width and center vertically
		d_x = (float)(W_WIDTH - 1) / (cols - 1);
		d_y = d_x / grid_aspect_ratio;
	} else
	{
		// Window is wider than grid aspect ratio, so fit to height and center horizontally
		d_y = (float)(W_HEIGHT - 1) / (rows - 1);
		d_x = d_y * grid_aspect_ratio;
	}

	float x_offset = (W_WIDTH - d_x * (cols - 1)) / 2;
	float y_offset = (W_HEIGHT - d_y * (rows - 1)) / 2;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			src[y][x].x = x * d_x + x_offset;
			src[y][x].y = y * d_y + y_offset;
		}
	}
}

int get_color_based_on_z(int z)
{
	// Example: simple mapping of z to a color
	// This function should be adjusted based on how you want to represent z values as colors
	int blue = 0x0000FF;
	int red = 0xFF0000;
	return (z > 0) ? red : blue; // Red for non-zero z, blue for zero
}

void breshenham(t_data *img, t_point p0, t_point p1)
{
	float x_step = p1.x - p0.x;
	float y_step = p1.y - p0.y;
	int max = fmax(fabs(x_step), fabs(y_step));
	x_step /= max;
	y_step /= max;

	// Define the colors based on z values
	int col_start = get_color_based_on_z(p0.z); // Convert p0.z to a color
	int col_end = get_color_based_on_z(p1.z); // Convert p1.z to a color

	for (int c = 0; c <= max; c++)
	{
		float ratio = (float)c / max;
		int color = get_color(ratio, col_start, col_end);
		my_mlx_pixel_put(img, round(p0.y + y_step * c), round(p0.x + x_step * c), color);
	}
}

void draw_points(t_data *img, t_point **src, int rows, int cols)
{
	t_vector2 i;

	for (i.y = 0; i.y < rows; i.y++)
	{
		for (i.x = 0; i.x < cols; i.x++)
		{
			if (i.x < cols - 1)
				breshenham(img, src[i.y][i.x], src[i.y][i.x + 1]);
			if (i.y < rows - 1)
				breshenham(img, src[i.y][i.x], src[i.y + 1][i.x]);
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
			gen_t_points(instance, filein);

			instance->mlx_ser = mlx_init();
			instance->mlx_win = mlx_new_window(instance->mlx_ser, W_WIDTH,W_HEIGHT, "fml");
			instance->mlx_img.img= mlx_new_image(instance->mlx_ser, W_WIDTH, W_HEIGHT);
			instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img, &instance->mlx_img.bits_per_pixel,
													&instance->mlx_img.line_length, &instance->mlx_img.endian);


			//convert_points(instance->source, instance->height, instance->width);
			//isometric_transform(instance);
			convert_points(instance->source, instance->height, instance->width);
			draw_points(&instance->mlx_img, instance->source, instance->height, instance->width);

			mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
			mlx_loop(instance->mlx_ser);

			free_t_points(instance->source, instance->height);
			free_t_points(instance->projection, instance->height);
		}
		free(instance);
		close(filein);
		printf("\n");
	}
	return(0);
}

