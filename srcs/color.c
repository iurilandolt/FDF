/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:48:01 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/10 12:33:48 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_session *instance, int color)
{
	t_vector2	i;

	i.y = 0;
	mlx_clear_window(instance->mlx_ser, instance->mlx_win);
	while (i.y < W_HEIGHT)
	{
		i.x = 0;
		while (i.x < W_WIDTH)
		{
			my_mlx_pixel_put(&(instance->mlx_img), i.x, i.y, color);
			i.x++;
		}
		i.y++;
	}
}

void	init_color(t_color *color, t_point *start, t_point *end)
{
	color->i = 0;
	if (start->c == 0)
	{
		if (start->z > 0)
			color->start = RED;
		else
			color->start = BLUE;
		if (end->z > 0)
			color->end = RED;
		else
			color->end = BLUE;
	}
	else
	{
		color->start = start->c;
		color->end = end->c;
	}
}

int	interpolate(float ratio, int start, int end)
{
	return (start * (1 - ratio) + end * ratio);
}

int	create_rgb(float ratio, int start, int end)
{
	int	r;
	int	g;
	int	b;

	r = interpolate(ratio, (start >> 16) & 0xFF, (end >> 16) & 0xFF);
	g = interpolate(ratio, (start >> 8) & 0xFF, (end >> 8) & 0xFF);
	b = interpolate(ratio, start & 0xFF, end & 0xFF);
	return ((r << 16) | (g << 8) | b);
}
