/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:06:52 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/23 22:14:44 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

//use vector 2 for temp cordinates
static void	isometric(t_point *point)
{
	int	x_tmp;
	int	y_tmp;

	x_tmp = point->x;
	y_tmp = point->y;
	point->x = (x_tmp - y_tmp) * cos(0.523599);
	point->y = (x_tmp + y_tmp) * sin(0.523599) - point->z;
}

static void	scale_map(t_session *instance, t_point *start, t_point *end)
{
	float	map_diagonal;
	float	factor;

	map_diagonal = sqrt(instance->width * instance->width + instance->height * instance->height);
	factor = 0.85 * W_HEIGHT / map_diagonal;
	start->x = round(start->x * factor);
	start->y = round(start->y * factor);
	end->x = round(end->x * factor);
	end->y = round(end->y * factor);
}

static void	center_map(t_point *start, t_point *end)
{
	int	x_offset;
	int	y_offset;

	x_offset = W_WIDTH * 2 / 5;
	y_offset = W_HEIGHT * 1 / 5;
	start->x += x_offset;
	start->y += y_offset;
	end->x += x_offset;
	end->y += y_offset;
}

void	transform_map(t_session *instance, t_point *start, t_point *end)
{
	scale_map(instance, start, end);
	isometric(start);
	isometric(end);
	center_map(start, end);
}
