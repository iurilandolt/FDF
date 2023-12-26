/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:48:01 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 15:22:31 by rlandolt         ###   ########.fr       */
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

int	interpolate(int start, int end, float ratio)
{
	return ((int)(start + ((end - start) * ratio)));
}
