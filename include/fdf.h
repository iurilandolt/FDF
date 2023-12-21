/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:20:03 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/21 15:42:19 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_session
{
	int		**source;
	int		height;
	int		width;
	void	*mlx_ser;
	void	*mlx_win;
	t_data	mlx_img;
}	t_session;

#define W_WIDTH 1920
#define W_HEIGHT 1080

// string methods
int		fdf_strlen(char *str);
int		ft_atoi(char *str);
int	tab_size(char **array);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
//split methods
void	*clear(char **array);
char	**ft_split(const char *str, char c);

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
int		check_fformat(t_session *instance, int filein);
int		open_file(t_session *instance, char *argv);

//libx methods
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
