/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 18:56:38 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include ".minilibx/mlx.h"
#include ".minilibx/mlx_int.h"

void	mlx_startup(t_session *instance)
{
	instance->mlx_ser = mlx_init();
	instance->mlx_win = mlx_new_window(instance->mlx_ser, W_WIDTH,W_HEIGHT, "42 FDF");
	instance->mlx_img.img = mlx_new_image(instance->mlx_ser, W_WIDTH, W_HEIGHT);
	instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img, &instance->mlx_img.bits_per_pixel,
											&instance->mlx_img.line_length, &instance->mlx_img.endian);
	// (if there !win !image ! data return? free t_points and instance and...)
	// mlx_shutdown(instance); ? mby will cause segfault
	draw_map(instance);
	mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
}

void	mlx_update(t_session *instance)
{
	clear_image(instance, 0);
	draw_map(instance);
	mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
}

void	mlx_shutdown(t_session *instance)
{
	if (instance->mlx_img.img)
		mlx_destroy_image(instance->mlx_ser, instance->mlx_img.img);
	if (instance->mlx_win)
	{
		mlx_destroy_window(instance->mlx_ser, instance->mlx_win);
		instance->mlx_win = NULL;
	}
	if (instance->mlx_ser)
	{
		mlx_destroy_display(instance->mlx_ser);
		free(instance->mlx_ser);
	}
	free_t_points(instance->source, instance->height);
	free(instance);
	exit(0);
}


//turn this function into the input handler for all keys // mlx_hook_loop
int	esc_pressed(int keycode, t_session *instance)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 65307)
		mlx_shutdown(instance);
	if (keycode == 65362)
	{
		instance->factor += 0.05;
		mlx_update(instance);
	}
	return (0);
}

//this will be the only function that intereacts with the window close button
// lets called exit hook or something
int window_closed(t_session *instance)
{
	printf("Window close event triggered.\n");
	mlx_shutdown(instance);
	return (0);
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
			build_t_point_grid(instance, filein);

			// function to inniate session variables
			instance->factor = 0.85;
			// shift y = someting;
			// shift x = something;
			mlx_startup(instance);

			mlx_hook(instance->mlx_win, DestroyNotify, StructureNotifyMask, window_closed, instance);
			mlx_hook(instance->mlx_win, 2, 1L<<0, esc_pressed, instance);
			mlx_loop(instance->mlx_ser);
		}
	}
	return(0);
}
