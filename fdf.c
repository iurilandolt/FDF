/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/22 18:13:49 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include ".minilibx/mlx.h"

void	isometric_transform(t_session *instance)
{
	t_transform	new;
	t_vector2	i;
	double		z;

	instance->projection = (t_point**)malloc(sizeof(t_point *) * instance->height);
	new.angle = 45.0;
	new.radian_angle = new.angle * M_PI / 180.0;
	i.y = 0;
	while (i.y < instance->height)
	{
		i.x = 0;
		instance->projection[i.y] =  (t_point *)malloc(sizeof(t_point) * instance->width);
		while (i.x < instance->width)
		{
			z = instance->source[i.y][i.x].z;

			instance->projection[i.y][i.x].x = z * cos(new.radian_angle);
			instance->projection[i.y][i.x].y = z * sin(new.radian_angle);
			instance->projection[i.y][i.x].z = instance->projection[i.y][i.x].x;

			i.x++;
		}
		i.y++;
	}
	print_t_points(instance->projection, instance->height, instance->width);
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

			isometric_transform(instance);

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

