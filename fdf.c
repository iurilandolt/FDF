/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/25 01:05:12 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include ".minilibx/mlx.h"
#include ".minilibx/mlx_int.h"

// mlx_shutdown().
void	destroy_mlx(t_session *instance)
{
	if (instance->mlx_img.img)
	{
		printf("destroying image\n");
		mlx_destroy_image(instance->mlx_ser, instance->mlx_img.img);
	}
	if (instance->mlx_win)
	{
		printf("destroying window\n");
		mlx_destroy_window(instance->mlx_ser, instance->mlx_win);
		instance->mlx_win = NULL;
	}
	if (instance->mlx_ser)
	{
		printf("destroying mlx\n");
		mlx_destroy_display(instance->mlx_ser);
		free(instance->mlx_ser);
	}
	free_t_points(instance->source, instance->height);
	free(instance);
	exit(0);
}

//turn this function into the input handler for all keys
int	esc_pressed(int keycode, t_session *instance)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 65307)
		destroy_mlx(instance);
	return (0);
}

//this will be the only function that intereacts with the window close button
int window_closed(t_session *instance)
{
	printf("Window close event triggered.\n");
		destroy_mlx(instance);
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
			gen_t_points(instance, filein);
			// function to manage mlx startup
			instance->mlx_ser = mlx_init();
			instance->mlx_win = mlx_new_window(instance->mlx_ser, W_WIDTH,W_HEIGHT, "fml");
			instance->mlx_img.img = mlx_new_image(instance->mlx_ser, W_WIDTH, W_HEIGHT);
			instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img, &instance->mlx_img.bits_per_pixel,
													&instance->mlx_img.line_length, &instance->mlx_img.endian);
			// (if there !win !image ! data return? free t_points and instance and...)
			draw_map(instance);
			mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
			mlx_hook(instance->mlx_win, DestroyNotify, StructureNotifyMask, window_closed, instance);
			mlx_hook(instance->mlx_win, 2, 1L<<0, esc_pressed, instance);
			mlx_loop(instance->mlx_ser);
		}
	}
	return(0);
}
