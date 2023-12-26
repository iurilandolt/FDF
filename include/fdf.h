/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:20:03 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 13:53:02 by rlandolt         ###   ########.fr       */
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
	float	x;
	float	y;
	float	z;
}	t_vector3;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	char	c[12];
}	t_point;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_bresenham
{
	int	x0;
	int	y0;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}		t_bresenham;

typedef struct s_session
{
	t_point	**source;
	int		height;
	int		width;
	float	factor;
	void	*mlx_ser;
	void	*mlx_win;
	t_data	mlx_img;
}	t_session;

#define W_WIDTH 1920
#define W_HEIGHT 1080

// string methods
int		ft_atoi(char *str);
int		tab_size(char **array);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
//split methods
void	*clear(char **array);
char	**ft_split(const char *str, char c);

//t_point methods
void	build_t_point_grid(t_session *instance, int filein);
void	print_t_points(t_point **grid, int height, int width);
void	free_t_points(t_point **grid, int height);
void print_t_points_info(t_point **grid, int height, int width);

//input check and file open
int		check_fext(char *path, char const *ext);
int		check_fformat(t_session *instance, int filein);
int		open_file(t_session *instance, char *argv);

//draw methods
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_session *instance, t_point *start, t_point *end);
void	draw_map(t_session *instance);

//transform methods
void	transform_map(t_session *instance, t_point *start, t_point *end);

//color
int	get_color(float ratio, int col_start, int col_end);
int	interpolate(int start, int end, float ratio);
#endif
