/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:20:03 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/20 19:46:19 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_vector3
{
	int	x;
	int	y;
	int	z;
}	t_vector3;

typedef struct s_session
{
	int		**source;
	int		height;
	int		width;
	void	*mlx;
	void	*win;


}	t_session;

// string methods
int		fdf_strlen(char *str);
int		ft_atoi(char *str);

//3D Array methods
int		***alloc_3d_grid(int height, int width, int depth);
void	free_3d_grid(int ***grid, int height, int width);
void	print_3d_grid(int ***grid, int height, int width, int depth);
//2D Array methods
int		**alloc_2d_grid(int height, int width);
void	free_2d_grid(int **grid, int height);
void	print_2d_grid(int **grid, int height, int width);
//input check and file open
int		check_fext(char *path, char const *ext);
int		check_fformat(int filein);
int		open_file(char *argv);

#endif
