/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/22 15:13:21 by rlandolt         ###   ########.fr       */
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

	i.y = 0;
	instance->source = (int**)malloc(sizeof(int *) * instance->height);
	while ((line = get_next_line(filein)) && i.y < instance->height)
	{
		i.x = 0;
		tab = ft_split(line, ' ');
		instance->width = tab_size(tab);
		instance->source[i.y] =  (int *)malloc(sizeof(int) * instance->width);
		while (tab[i.x] && i.x < instance->width)
		{
			instance->source[i.y][i.x] = ft_atoi(tab[i.x]);
			i.x++;
		}
		clear(tab);
		free(line);
		i.y++;
	}
	print_2d_grid(instance->source, instance->height, instance->width);
}

void	isometric_transform(t_session *instance)
{
	t_transform	new;
	t_vector2	i;
	double		z;

	instance->projection = (int**)malloc(sizeof(int *) * instance->height);
	new.angle = 45.0;
	new.radian_angle = new.angle * M_PI / 180.0;
	i.y = 0;
	while (i.y < instance->height)
	{
		i.x = 0;
		instance->projection[i.y] =  (int *)malloc(sizeof(int) * instance->width);
		while (i.x < instance->width)
		{
			z = instance->source[i.y][i.x];
			new.x = z * cos(new.radian_angle);
			new.y = z * sin(new.radian_angle);
			instance->projection[i.y][i.x] = (int)new.x;
			i.x++;
		}
		i.y++;
	}
	print_2d_grid(instance->projection, instance->height, instance->width);
}

void	my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_points(t_data *img, int **src, int rows, int cols)
{
	t_vector2	d;
	t_vector2	i;
	t_vector2	center;

	d.y = W_HEIGHT / rows;
	d.x = W_WIDTH / cols;

	i.y = 0;
	while (i.y < rows)
	{
		i.x = 0;
		while (i.x < cols)
		{
			center.y = i.y * d.y + d.y / 2;
			center.x = i.x * d.x + d.x / 2;
			my_mlx_pixel_put(img, center.y, center.x, src[i.y][i.x] * 25);
			i.x++;
		}
		i.y++;
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

			//isometric_transform(instance);

			draw_points(&instance->mlx_img, instance->source, instance->height, instance->width);

			mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
			mlx_loop(instance->mlx_ser);

			free_2d_grid(instance->source, instance->height);
			free_2d_grid(instance->projection, instance->height);
		}
		free(instance);
		close(filein);
		printf("\n");
	}
	return(0);
}

