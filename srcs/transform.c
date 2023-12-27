/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:06:52 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/27 13:25:33 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"


void	convert_points(t_point *start, t_point *end)
{
	t_vector2	tmp;

	tmp.x = start->x;
	tmp.y = start->y;
	start->x = (tmp.x - tmp.y) * cos(0.523599);
	start->y = (tmp.x + tmp.y) * sin(0.523599) - start->z;

	tmp.x = end->x;
	tmp.y = end->y;
	end->x = (tmp.x - tmp.y) * cos(0.523599);
	end->y = (tmp.x + tmp.y) * sin(0.523599) - end->z;
}

void	scale_points(t_session *instance, t_point *start, t_point *end)
{
	float	map_diagonal;
	float	factor;

	map_diagonal = sqrt(instance->width * instance->width + instance->height * instance->height);
	factor = instance->factor * W_HEIGHT / map_diagonal;
	start->x = round(start->x * factor);
	start->y = round(start->y * factor);
	end->x = round(end->x * factor);
	end->y = round(end->y * factor);
}

void	center_points(t_session *instance, t_point *start, t_point *end)
{
	t_vector2	offset;

	offset.x = instance->offset.x;
	offset.y = instance->offset.y;
	start->x += offset.x;
	start->y += offset.y;
	end->x += offset.x;
	end->y += offset.y;
}

void	transform_points(t_session *instance, t_point *start, t_point *end)
{
	scale_points(instance, start, end);
	if (instance->iso)
		convert_points(start, end);
	center_points(instance, start, end);
}

