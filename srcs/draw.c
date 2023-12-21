/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:40:06 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/21 15:44:31 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

//draw_circle(&instance->mlx_img, WIDTH / 2, HEIGHT /2, 500, 0x00FF0000);
void draw_circle(t_data *data, int cx, int cy, int radius, int color)
{
	for (int y = cy - radius; y <= cy + radius; ++y)
	{
		for (int x = cx - radius; x <= cx + radius; ++x)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius)
			{
				my_mlx_pixel_put(data, x, y, color);
			}
		}
	}
}

void draw_rectangle(t_data *data, int height, int width, int color)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}
