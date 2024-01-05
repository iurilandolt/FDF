/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:06:52 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/05 12:46:26 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"
/*
 * Converts Cartesian coordinates to isometric coordinates for both start and end points.
 * 30 degrees (or 0.523599 radians) isometric.
 * - Skewing: Calculated by (x - y) and (x + y) operations.
 * - Rotation: Applied using cosine and sine of 30 degrees to the skewed coordinates.
 * - Elevation Adjustment: The z-coordinate value is subtracted from the y-coordinate.
 */
void	convert_points(t_session *instance, t_point *start, t_point *end)
{
	t_vector2	tmp;

	if (!instance->iso)
	{
		if (instance->ort)
			return ;
		start->y = -start->z;
		end->y = -end->z;
		return ;
	}
	tmp.x = start->x;
	tmp.y = start->y;
	start->x = (tmp.x - tmp.y) * cos(DEG30);
	start->y = (tmp.x + tmp.y) * sin(DEG30) - start->z;
	tmp.x = end->x;
	tmp.y = end->y;
	end->x = (tmp.x - tmp.y) * cos(DEG30);
	end->y = (tmp.x + tmp.y) * sin(DEG30) - end->z;
}

/*
 * Scales the points based on the window size and the diagonal length of the grid.
 * calculates a scaling factor that ensures the grid fits proportionally
 * within the window.
 */
void	scale_points(t_session *instance, t_point *start, t_point *end)
{
	float	diagonal;
	float	factor;

	diagonal = hypot(instance->width, instance->height);
	factor = instance->factor * W_HEIGHT / diagonal;
	start->x = round(start->x * factor);
	start->y = round(start->y * factor);
	start->z = round(start->z * instance->factor);
	end->x = round(end->x * factor);
	end->y = round(end->y * factor);
	end->z = round(end->z * instance->factor);
}
/*
* Adjusts the position of the points by a fixed offset,
* allows translation.
*/

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

void rotate_zaxis(t_session *instance, t_point *start, t_point *end)
{
	t_vector2 tmp;

	tmp.x = start->x;
	tmp.y = start->y;
	start->x = tmp.x * cos(instance->angle) - tmp.y * sin(instance->angle);
	start->y = tmp.x * sin(instance->angle) + tmp.y * cos(instance->angle);
	tmp.x = end->x;
	tmp.y = end->y;
	end->x = tmp.x * cos(instance->angle) - tmp.y * sin(instance->angle);
	end->y = tmp.x * sin(instance->angle) + tmp.y * cos(instance->angle);

}

void	transform_points(t_session *instance, t_point *start, t_point *end)
{
	scale_points(instance, start, end);
	if (instance->angle != 0)
		rotate_zaxis(instance ,start, end);
	convert_points(instance, start, end);
	center_points(instance, start, end);
}
