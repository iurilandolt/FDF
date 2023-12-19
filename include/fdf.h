/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:20:03 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/19 18:26:33 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>

// string methods
int	ft_strlen(char *str);

//3D Array methods
int		***alloc_3d_grid(int width, int height, int depth);
void	free_3d_grid(int ***grid, int height, int width);
void	print_3d_grid(int ***grid, int height, int width, int depth);
//2D Array methods
int		**alloc_2d_grid(int width, int height);
void	free_2d_grid(int **grid, int height);
void	print_2d_grid(int **grid, int height, int width);

#endif
