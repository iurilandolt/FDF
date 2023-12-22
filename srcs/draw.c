/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/22 18:13:16 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

void	my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_points(t_data *img, t_point **src, int rows, int cols)
{
	t_vector2	d;
	t_vector2	i;
	t_vector2	center;

	d.y = W_HEIGHT / rows;
	d.x = W_WIDTH / cols;

	i.y = 0;
	while (i.y < rows)
	{
		i.x = 0;
		while (i.x < cols)
		{
			center.y = src[i.y][i.x].y * d.y + d.y / 2;
			center.x = src[i.y][i.x].x * d.x + d.x / 2;
			my_mlx_pixel_put(img, center.y, center.x, src[i.y][i.x].z * 25);
			i.x++;
		}
		i.y++;
	}
}
