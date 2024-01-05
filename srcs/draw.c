/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/05 15:11:09 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"
/*
 * Initialize DDA (Digital Differential Analyzer) algorithm parameters for line drawing.
 * Sets the current position to the start point and calculates the deltas (differences)
 * in x and y coordinates between the start and end points. Determines the number of
 * steps required to draw the line based on the maximum delta value. Sets the increment
 * size for each step in x and y directions.
 * fmax -> returns largest of two numbers, fabs -> returns absolute value of a number
 */
void	init_dda(t_dda *params, t_point *start, t_point *end)
{
	params->current_x = start->x;
	params->current_y = start->y;
	params->delta_x = end->x - start->x;
	params->delta_y = end->y - start->y;
	params->step = fmax(fabs(params->delta_x), fabs(params->delta_y));
	params->x_inc = params->delta_x / params->step;
	params->y_inc = params->delta_y / params->step;
}
/*
* initiliaze values for line drawing algorithm
* checks for color in t_point, if no color is found, one is given based on z value
* color pixel acorddlingly to ratio beetwen start and end points
*/
void	put_pixels(t_session *instance, t_point *start, t_point *end)
{
	t_dda	params;
	t_color	color;
	int		pixel_color;

	init_dda(&params, start, end);
	init_color(&color, start, end);
	while (color.i <= params.step)
	{
		color.step = color.i / params.step;
		pixel_color = create_rgb(color.step, color.start, color.end);
		my_mlx_pixel_put(&instance->mlx_img,
			round(params.current_x), round(params.current_y), pixel_color);
		params.current_x += params.x_inc;
		params.current_y += params.y_inc;
		color.i++;
	}
}
/*
*	check line orientation, create temporary t_points to hold values from struct array index
*	convert points to isometric if needed, scales and centers points to window size
*	send points to put_pixels
*/
void	draw_lines(t_session *instance, int x, int y, int orientation)
{
	t_point	start;
	t_point	end;

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
/*
* iterate all points in struct array and draw corresponding lines within broundaries
*/

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
	t_vector2 i;

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
