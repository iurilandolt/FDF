/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:48:01 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/02 21:59:19 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > W_WIDTH || y > W_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_color(t_color *color, t_point *start, t_point *end)
{
	color->i = 0;
	if (start->c == 0)
	{
		if (start->z > 0)
			color->c_start = ORANGE;
		else
			color->c_start = PURPLE;
		if (end->z > 0)
			color->c_end = ORANGE;
		else
			color->c_end = PURPLE;
	}
	else
	{
		color->c_start = start->c;
		color->c_end = end->c;
	}
}

int	get_color(float ratio, int col_start, int col_end)
{
	int	r;
	int	g;
	int	b;

	r = ((col_start >> 16) & 0xFF) * (1 - ratio)
		+ ((col_end >> 16) & 0xFF) * ratio;
	g = ((col_start >> 8) & 0xFF) * (1 - ratio)
		+ ((col_end >> 8) & 0xFF) * ratio;
	b = (col_start & 0xFF) * (1 - ratio) + (col_end & 0xFF) * ratio;
	return ((r << 16) | (g << 8) | b);
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
