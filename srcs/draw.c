/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/27 15:42:09 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

void init_dda(t_dda *params, t_point *start, t_point *end)
{
	params->current_x = start->x;
	params->current_y = start->y;
	params->delta_x = end->x - start->x;
	params->delta_y = end->y - start->y;
	params->step = fmax(fabs(params->delta_x), fabs(params->delta_y));
	params->x_inc = params->delta_x / params->step;
	params->y_inc = params->delta_y / params->step;
}

void put_pixels(t_session *instance, t_point *start, t_point *end)
{
	t_dda params;
	t_color color;

	init_dda(&params, start, end);
	init_color(params, &color, start, end);
	while (color.i <= params.step)
	{
		color.c_ratio = (float)color.i / color.max;
		my_mlx_pixel_put(&instance->mlx_img, round(params.current_x), round(params.current_y),
				get_color(color.c_ratio, color.c_start, color.c_end));
		params.current_x += params.x_inc;
		params.current_y += params.y_inc;
		color.i++;
	}
}

void draw_lines(t_session *instance, int x, int y, int orientation)
{
	t_point start;
	t_point end;

	start.x = x;
	start.y = y;
	start.z = instance->source[y][x].z;
	start.c = instance->source[y][x].c;

	if (orientation == 0)
	{
		end.x = x + 1;
		end.y = y;
		end.z = instance->source[y][x + 1].z;
		end.c = instance->source[y][x + 1].c;
	}
	else
	{
		end.x = x;
		end.y = y + 1;
		end.z = instance->source[y + 1][x].z;
		end.c = instance->source[y + 1][x].c;
	}
	transform_points(instance, &start, &end);
	put_pixels(instance, &start, &end);
}

void	draw_map(t_session *instance)
{
	t_vector2 i;

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
