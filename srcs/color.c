/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:48:01 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/04 20:14:37 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"
/*
* custom pixel put function, places pixels in img file that serves as buffer before pushing img to window
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
/*
 * set all pixels to black in the img.
 * used to clear window before printing a new image
*/
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
/*
* set t_point color according to z value if no color is provided by the map
*/
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
/*
* interpolates between two integer values based on a given ratio.
* ratio is a float between 0 and 1
* ratio of 0.0 will return the `start` value, a ratio of 1.0 will return the `end` value,
*/
int	interpolate(float ratio, int start, int end)
{
	return (start * (1 - ratio) + end * ratio);
}
/*
* uses interpolate function to exctract the 8 bits relative to each color
* (red, green, blue) from a single interger value start/end
* returns color value according to current ratio
*/
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

