/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 17:15:12 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

static void	bresenham_define(t_bresenham *param, t_point *start, t_point *end)
{

	param->dx = abs(end->x - start->x);
	param->dy = -1 * abs(end->y - start->y);

	if (start->x <= end->x)
		param->sx = 1;
	else
		param->sx = -1;
	if (start->y <= end->y)
		param->sy = 1;
	else
		param->sy = -1;

	param->err = param->dx + param->dy;
	param->x0 = start->x;
	param->y0 = start->y;
}

void	draw_line(t_session *instance, t_point *start, t_point *end)
{
	t_bresenham	param;
	t_color 	color;

	transform_map(instance, start, end);
	bresenham_define(&param, start, end);
	init_color(param, &color, start, end);
	while (1)
	{
		color.c_ratio = (float)color.i / color.max;
		color.i++;
		if (param.x0 < W_WIDTH && param.x0 > 0 && param.y0 < W_HEIGHT && param.y0 > 0)
			my_mlx_pixel_put(&instance->mlx_img, param.x0, param.y0, get_color(color.c_ratio, color.c_start, color.c_end));
		if (param.x0 == end->x && param.y0 == end->y)
			break ;
		if (2 * param.err >= param.dy && param.x0 != end->x)
		{
			param.err += param.dy;
			param.x0 += param.sx;
		}
		if (2 * param.err <= param.dx && param.y0 != end->y)
		{
			param.err += param.dx;
			param.y0 += param.sy;
		}
	}
}

// why have t point variables here? just for readability?
static void	draw_horizontal_lines(t_session *instance, int x, int y)
{
	t_point	a;
	t_point	b;

	a.x = x;
	a.y = y;
	a.z = instance->source[y][x].z;
	a.c = instance->source[y][x].c;
	b.x = x + 1;
	b.y = y;
	b.z = instance->source[y][x + 1].z;
	b.c = instance->source[y][x + 1].c;
	draw_line(instance, &a, &b);
}
// arent a and b just start and end?
static void	draw_vertical_lines(t_session *instance, int x, int y)
{
	t_point	a;
	t_point	b;

	a.x = x;
	a.y = y;
	a.z = instance->source[y][x].z;
	a.c = instance->source[y][x].c;
	b.x = x;
	b.y = y + 1;
	b.z = instance->source[y + 1][x].z;
	b.c = instance->source[y + 1][x].c;
	draw_line(instance, &a, &b);
}

//change to vector2
void	draw_map(t_session *instance)
{
	int	x;
	int	y;

	y = 0;

	while (y < instance->height)
	{
		x = 0;
		while (x < instance->width)
		{
			if (x < instance->width - 1)
			{
				draw_horizontal_lines(instance, x, y);
			}
			if (y < instance->height - 1)
			{
				draw_vertical_lines(instance, x, y);
			}
			x++;
		}
		y++;
	}
}
