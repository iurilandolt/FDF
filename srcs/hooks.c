/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:53:09 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/27 22:26:29 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	exit_hook(t_session *instance)
{
	mlx_shutdown(instance);
	return (0);
}

void	swap_projection(t_session *instance)
{
	if (instance->iso)
		instance->iso = false;
	else
		instance->iso = true;
}

int	handle_key(int keycode, t_session *instance)
{
	if (keycode == ESC)
		mlx_shutdown(instance);
	if (keycode == UP)
		instance->offset.y -= 10;
	if (keycode == DOWN)
		instance->offset.y += 10;
	if (keycode == LEFT)
		instance->offset.x -= 10;
	if (keycode == RIGHT)
		instance->offset.x += 10;
	if (keycode == PLUS)
		instance->factor -= 0.05;
	if (keycode == MINUS)
		instance->factor += 0.05;
	if (keycode == SWAP)
		swap_projection(instance);
	mlx_update(instance);
	return (0);
}
