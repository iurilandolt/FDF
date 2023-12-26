/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:06:52 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 14:01:58 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../.minilibx/mlx.h"

void	isometric(t_point *point)
{
	t_vector2	tmp;

	tmp.x = point->x;
	tmp.y = point->y;
	point->x = (tmp.x - tmp.y) * cos(0.523599);
	point->y = (tmp.x + tmp.y) * sin(0.523599) - point->z;
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

/*implement scaling/aka zooming
typedef struct s_session {
    // ... existing members ...
    float zoom_factor;
} t_session;

void scale_zoom(t_session *instance, t_point *start, t_point *end) {
    start->x = round(start->x * instance->zoom_factor);
    start->y = round(start->y * instance->zoom_factor);
    end->x = round(end->x * instance->zoom_factor);
    end->y = round(end->y * instance->zoom_factor);
}

*/

//offset might be read/set from/to session struct
void	center_isometric(t_point *start, t_point *end)
{
	t_vector2	offset;

	offset.x = W_WIDTH * 2 / 5;
	offset.y = W_HEIGHT * 1 / 5;
	start->x += offset.x;
	start->y += offset.y;
	end->x += offset.x;
	end->y += offset.y;
}

void	transform_map(t_session *instance, t_point *start, t_point *end)
{
	scale_isometric(instance, start, end);
	isometric(start);
	isometric(end);
	center_isometric(start, end);
}

/*implement x/y shifting

typedef struct s_session {
    // ... existing members ...
    int offset_x;
    int offset_y;
} t_session;

void center_isometric(t_session *instance, t_point *start, t_point *end) {
    start->x += instance->offset_x;
    start->y += instance->offset_y;
    end->x += instance->offset_x;
    end->y += instance->offset_y;
}


*/
