/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:53:09 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/05 12:45:32 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	exit_hook(t_session *instance)
{
	mlx_shutdown(instance);
	return (0);
}

void swap_projection(t_session *instance)
{
	if (instance->iso && !instance->ort)
	{
		instance->iso = false;
		instance->ort = true;
	}
	else if (!instance->iso && instance->ort)
		instance->ort= false;

	else
		instance->iso = true;
}

void	rotate_hook(t_session *instance)
{
	if (instance->angle < 4)
		instance->angle += DEG90;
	else
		instance->angle = 0;

}

void	reset_projection(t_session *instance)
{
	instance->offset.x = W_WIDTH * 0.4;
	instance->offset.y = W_HEIGHT * 0.2;
	instance->factor = 1.0;
	instance->angle = 0;
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
	if (keycode == PLUS && instance->factor < 7.0)
		instance->factor += 0.05;
	if (keycode == MINUS && instance->factor > 0.2)
		instance->factor -= 0.05;
	if (keycode == SWAP)
		swap_projection(instance);
	if (keycode == ROTATE)
		rotate_hook(instance);
	if (keycode == CENTER)
		reset_projection(instance);
	mlx_update(instance);
	return (0);
}
