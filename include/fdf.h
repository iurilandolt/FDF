/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:20:03 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/27 15:32:26 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

typedef struct s_vector2
{
	int	x;
	int	y;

}	t_vector2;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		c;
}	t_point;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_dda
{
	float	delta_x;
	float	delta_y;
	float	step;
	float	x_inc;
	float	y_inc;
	float	current_x;
	float	current_y;
}	t_dda;

typedef struct s_color
{
	int		max;
	int		c_start;
	int		c_end;
	int		i;
	float	c_ratio;
} t_color;

typedef struct s_session
{
	t_point	**source;
	t_vector2	offset;
	int			height;
	int			width;
	float		factor;
	bool		iso;
	void		*mlx_ser;
	void		*mlx_win;
	t_data		mlx_img;
}	t_session;

#define W_WIDTH 1920
#define W_HEIGHT 1080

#define RED 0xFF2000
#define BLUE 0x2000FF

#define ESC 65307
#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363
#define PLUS 45
#define MINUS 61
#define SWAP 112

// string methods
int		ft_atoi(char *str);
int		ft_atohex(const char *str);
int		tab_size(char **array);
void	ft_strlcpy(char *dest, const char *src, size_t size);

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
void	put_pixels(t_session *instance, t_point *start, t_point *end);
void	draw_map(t_session *instance);

//transform methods
void	transform_points(t_session *instance, t_point *start, t_point *end);

//color methods
int		get_color(float ratio, int col_start, int col_end);
void	init_color(t_dda param, t_color *color, t_point *start, t_point *end);
void	clear_image(t_session *instance, int color);

//hook methods
int exit_hook(t_session *instance);
int	handle_key(int keycode, t_session *instance);

//mlx methods
void	mlx_shutdown(t_session *instance);
void	mlx_update(t_session *instance);
#endif
