/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/24 14:29:01 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst; // pixel address

	if (x < 0 || y < 0 || x > W_WIDTH || y > W_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int get_color_based_on_z(int z)
{
	return (z > 0) ? 0xFF0000 : 0x0000FF;
}

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

	transform_map(instance, start, end);
	bresenham_define(&param, start, end);

	int max = fmax(fabs((float)param.dx), fabs((float)param.dy));
	int col_start = get_color_based_on_z(start->z); // Convert p0.z to a color
	int col_end = get_color_based_on_z(end->z); // Convert p1.z to a color
	int c = 0;

	while (1)
	{
		float ratio = (float)c / max;
		c++;
		if (param.x0 < W_WIDTH && param.x0 > 0 && param.y0 < W_HEIGHT && param.y0 > 0)
			my_mlx_pixel_put(&instance->mlx_img, param.x0, param.y0, get_color(ratio, col_start, col_end));
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

	b.x = x + 1;
	b.y = y;
	b.z = instance->source[y][x + 1].z;

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

	b.x = x;
	b.y = y + 1;
	b.z = instance->source[y + 1][x].z;

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
