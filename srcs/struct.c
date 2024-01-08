/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:53:52 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/08 16:14:42 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/gnl.h"

void	set_t_point_values(t_point *point, int x, int y, char *tab)
{
	char		**color;

	color = ft_split(tab, ',');
	point->x = x;
	point->y = y;
	point->z = ft_atoi(tab);
	point->c = 0;
	if (color[1])
		point->c = ft_atohex(color[1]);
	clear(color);
}

void	build_t_point_grid(t_session *instance, int filein)
{
	char		*line;
	char		**tab;
	t_vector2	i;

	i.y = 0;
	instance->source = (t_point **)malloc(sizeof(t_point *) * instance->height);
	line = get_next_line(filein);
	while (line && i.y < instance->height)
	{
		i.x = 0;
		tab = ft_split(line, ' ');
		instance->width = tab_size(tab);
		instance->source[i.y] = (t_point *)malloc(sizeof(
					t_point) * instance->width);
		while (tab[i.x] && i.x < instance->width)
		{
			set_t_point_values(&instance->source[i.y][i.x], i.x, i.y, tab[i.x]);
			i.x++;
		}
		clear(tab);
		free(line);
		i.y++;
		line = get_next_line(filein);
	}
	free(line);
}

void	free_t_points(t_point **grid, int height)
{
	int	y;

	y = 0;
	while (y < height)
		free(grid[y++]);
	free(grid);
}

int	check_bounds(t_point *start, t_point *end)
{
	if (start->x < -MOD || start->y < -MOD)
		return (0);
	if (end->x < -MOD || end->y < -MOD)
		return (0);
	if (start->x > W_WIDTH + MOD || start->y > W_HEIGHT + MOD)
		return (0);
	if (end->x > W_WIDTH + MOD || end->y > W_HEIGHT + MOD)
		return (0);
	return (1);
}

void	offset_for_angle(t_session *instance, t_vector2 *offset)
{
	if (instance->angle > 0 && instance->angle < 3)
	{
		offset->x += W_WIDTH * (0.4 * instance->factor);
		offset->y += W_HEIGHT * (0.4 * instance->factor);
	}
	else if (instance->angle > 3 && instance->angle < 4)
	{
		offset->x += W_WIDTH * (0.1 * instance->factor);
		offset->y += W_HEIGHT * (0.7 * instance->factor);
	}
	else if (instance->angle > 4)
	{
		offset->x -= W_WIDTH * 0.2 * (instance->factor);
		offset->y += W_HEIGHT * 0.4 * (instance->factor);
	}
}
