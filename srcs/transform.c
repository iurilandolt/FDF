/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:06:52 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 22:49:10 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

void	convert_isometric(t_point *point)
{
	t_vector2	tmp;

	tmp.x = point->x;
	tmp.y = point->y;
	point->x = (tmp.x - tmp.y) * cos(0.523599);
	point->y = (tmp.x + tmp.y) * sin(0.523599) - point->z;
}

void	scale_isometric(t_session *instance, t_point *start, t_point *end)
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

void	center_isometric(t_session *instance, t_point *start, t_point *end)
{
	t_vector2	offset;

	offset.x = instance->offset.x;
	offset.y = instance->offset.y;
	start->x += offset.x;
	start->y += offset.y;
	end->x += offset.x;
	end->y += offset.y;
}

void	transform_map(t_session *instance, t_point *start, t_point *end)
{
	scale_isometric(instance, start, end);
	convert_isometric(start);
	convert_isometric(end);
	center_isometric(instance, start, end);
}

/*
return to orthographic projection ->
will need its own centering function, scaling might be different
void orthographic(t_point *point)
{
	t_vector2	og;

	og.x = (point->x / cos(0.523599) + point->y / sin(0.523599)) / 2;
	og.y = (point->y / sin(0.523599) - point->x / cos(0.523599)) / 2;
	point->x = og.x;
	point->y = og.y;
}
*/
