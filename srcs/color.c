/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:48:01 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 17:17:10 by rlandolt         ###   ########.fr       */
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

void	init_color(t_bresenham param, t_color *color, t_point *start, t_point *end)
{
	color->max = fmax(fabs((float)param.dx), fabs((float)param.dy));
	if (start->c == 0)
	{
		color->c_start = get_color_based_on_z(start->z);
		color->c_end = get_color_based_on_z(end->z);
	}
	else
	{
		color->c_start = start->c;
		color->c_end = end->c;
	}
	color->i = 0;
}

int	interpolate(int start, int end, float ratio)
{
	return ((int)(start + ((end - start) * ratio)));
}

int	get_color(float ratio, int col_start, int col_end)
{
	int	r;
	int	g;
	int	b;

	r = interpolate((col_start >> 16) & 0xFF, (col_end >> 16) & 0xFF, ratio);
	g = interpolate((col_start >> 8) & 0xFF, (col_end >> 8) & 0xFF, ratio);
	b = interpolate(col_start & 0xFF, col_end & 0xFF, ratio);
	return ((r << 16) | (g << 8) | b);
}


