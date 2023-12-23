/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:24:49 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/23 19:02:08 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include ".minilibx/mlx.h"

int get_color_based_on_z(int z)
{
	// Example: simple mapping of z to a color
	// This function should be adjusted based on how you want to represent z values as colors
	int blue = 0x0000FF;
	int red = 0xFF0000;
	return (z > 0) ? red : blue; // Red for non-zero z, blue for zero
}

/*
void	breshenham(t_session *instance, t_point pt1, t_point pt2)
{
	float	x_step;
	float	y_step;
	float	ratio;
	int		max;
	int		c;

	c = 0;
	ratio = 0;
	x_step = pt2.x - pt1.x;
	y_step = pt2.y - pt1.y;
	max = fmax(fabs(x_step), fabs(y_step));
	x_step /= max;
	y_step /= max;

	int col_start = get_color_based_on_z(pt1.z); // Convert p0.z to a color
	int col_end = get_color_based_on_z(pt2.z); // Convert p1.z to a color

	while (((int)(pt1.x - pt2.x) || (int)(pt1.y - pt2.y)) && c <= max) //
	{
		ratio = (float)c / max;
		printf("Drawing pixel at (%.2f, %.2f) with color %x\n", pt1.x + x_step * c, pt1.y + y_step * c, get_color(ratio, col_start, col_end));
		my_mlx_pixel_put(&(instance->mlx_img), pt1.x, pt1.y, get_color(ratio, col_start, col_end));
		pt1.x += x_step;
		pt1.y += y_step;
		c++;
	}
}
*/
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

void	set_zoom(t_session *instance, t_point *pt1, t_point *pt2)
{
	pt1->x *= instance->zoom;
	pt1->y *= instance->zoom;
	pt2->x *= instance->zoom;
	pt2->y *= instance->zoom;
}

void	set_steepness(t_session *instance, int *z, int *z1)
{
	*z *= instance->steepness;
	*z1 *= instance->steepness;
}

void	set_shift(t_session *instance, t_point *pt1, t_point *pt2)
{
	pt1->x += instance->shift_x;
	pt1->y += instance->shift_y;
	pt2->x += instance->shift_x;
	pt2->y += instance->shift_y;
}

void set_isometric(t_point *p, int z) {
	p->x = (p->x - p->y) * cos(0.8);
	p->y = (p->x + p->y) * sin(0.8) - z;
}

void	set_parallel(t_point *p, int z)
{
	p->x = p->x - z;
	p->y = p->y - z;
}

void	projection(t_point *pt1, t_point *pt2, t_point zpt)
{
		//set_isometric(pt1, zpt.x);
		//set_isometric(pt2, zpt.y);

		set_parallel(pt1, zpt.x);
		set_parallel(pt2, zpt.y);
}

void	draw_line(t_session *instance, t_point pt1, t_point pt2)
{
	int		z;
	int		z1;
	t_point	zpt;

	z = instance->source[(int)pt1.y][(int)pt1.x].z;
	z1 = instance->source[(int)pt2.y][(int)pt2.x].z;
	set_zoom(instance, &pt1, &pt2);
	set_steepness(instance, &z, &z1);
	zpt.x = z;
	zpt.y = z1;
	projection(&pt1, &pt2, zpt);
	set_shift(instance, &pt1, &pt2);
	breshenham(&(instance->mlx_img), pt1, pt2);
}

void	draw2(t_session *instance, t_point *pt1, t_point *pt2, t_point *curr_pt)
{
	if (curr_pt->x < (instance->width - 1))
	{
		pt1->x = curr_pt->x;
		pt1->y = curr_pt->y;
		pt2->x = curr_pt->x + 1;
		pt2->y = curr_pt->y;
		draw_line(instance,*pt1, *pt2);
	}
	if (curr_pt->y < (instance->height - 1))
	{
		pt1->x = curr_pt->x;
		pt1->y = curr_pt->y;
		pt2->x = curr_pt->x;
		pt2->y = curr_pt->y + 1;
		draw_line(instance,*pt1, *pt2);
	}
}

void	draw(t_session *instance)
{
	t_point	curr_pt;
	t_point	pt1;
	t_point	pt2;

	curr_pt.y = 0;
	while (curr_pt.y < (instance->height - 1))
	{
		curr_pt.x = 0;
		while (curr_pt.x < instance->width - 1)
		{
			draw2(instance, &pt1, &pt2, &curr_pt);
			curr_pt.x++;
		}
		curr_pt.y++;
	}
	print_t_points_info(instance->source, instance->height, instance->width);
}

void	init_fdf(t_session *instance)
{
	instance->shift_x = 10; //W_WIDTH / 2;
	instance->shift_y = 10; //W_HEIGHT / 2;
	instance->zoom = 25;
	instance->steepness = 3;
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

			init_fdf(instance);
			draw(instance);

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

