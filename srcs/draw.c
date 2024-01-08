/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/08 16:21:44 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

void	init_dda(t_dda *dda, t_point *start, t_point *end)
{
	dda->current_x = start->x;
	dda->current_y = start->y;
	dda->delta_x = end->x - start->x;
	dda->delta_y = end->y - start->y;
	dda->step = fmax(fabs(dda->delta_x), fabs(dda->delta_y));
	dda->x_inc = dda->delta_x / dda->step;
	dda->y_inc = dda->delta_y / dda->step;
}

void	put_pixels(t_session *instance, t_point *start, t_point *end)
{
	t_dda	dda;
	t_color	color;
	int		pixel_color;

	init_dda(&dda, start, end);
	init_color(&color, start, end);
	while (color.i <= dda.step)
	{
		color.step = color.i / dda.step;
		pixel_color = create_rgb(color.step, color.start, color.end);
		my_mlx_pixel_put(&instance->mlx_img,
			round(dda.current_x), round(dda.current_y), pixel_color);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		color.i++;
	}
}

void	draw_lines(t_session *instance, int x, int y, int orientation)
{
	t_point	start;
	t_point	end;

	start = instance->source[y][x];
	if (orientation == 0)
		end = instance->source[y][x + 1];
	else
		end = instance->source[y + 1][x];
	transform_points(instance, &start, &end);
	if (!check_bounds(&start, &end))
		return ;
	put_pixels(instance, &start, &end);
}

void	draw_map(t_session *instance)
{
	t_vector2	i;

	i.y = 0;
	while (i.y < instance->height)
	{
		i.x = 0;
		while (i.x < instance->width)
		{
			if (i.x < instance->width - 1)
				draw_lines(instance, i.x, i.y, 0);
			if (i.y < instance->height - 1)
				draw_lines(instance, i.x, i.y, 1);
			i.x++;
		}
		i.y++;
	}
}

void	reverse_draw_map(t_session *instance)
{
	t_vector2	i;

	i.y = instance->height - 1;
	while (i.y >= 0)
	{
		i.x = instance->width - 1;
		while (i.x >= 0)
		{
			if (i.x > 0)
				draw_lines(instance, i.x - 1, i.y, 0);
			if (i.y > 0)
				draw_lines(instance, i.x, i.y - 1, 1);
			i.x--;
		}
		i.y--;
	}
}
