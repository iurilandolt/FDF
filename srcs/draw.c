/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 18:33:02 by rlandolt         ###   ########.fr       */
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

static void	draw_horizontal_lines(t_session *instance, int x, int y)
{
	t_point	start;
	t_point	end;

	start.x = x;
	start.y = y;
	start.z = instance->source[y][x].z;
	start.c = instance->source[y][x].c;
	end.x = x + 1;
	end.y = y;
	end.z = instance->source[y][x + 1].z;
	end.c = instance->source[y][x + 1].c;
	draw_line(instance, &start, &end);
}

static void	draw_vertical_lines(t_session *instance, int x, int y)
{
	t_point	start;
	t_point	end;

	start.x = x;
	start.y = y;
	start.z = instance->source[y][x].z;
	start.c = instance->source[y][x].c;
	end.x = x;
	end.y = y + 1;
	end.z = instance->source[y + 1][x].z;
	end.c = instance->source[y + 1][x].c;
	draw_line(instance, &start, &end);
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
				draw_horizontal_lines(instance, i.x, i.y);
			if (i.y < instance->height - 1)
				draw_vertical_lines(instance, i.x, i.y);
			i.x++;
		}
		i.y++;
	}
}
