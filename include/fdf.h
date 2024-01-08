/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:20:03 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/08 16:39:53 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>

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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_dda
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
	int		start;
	int		end;
	int		i;
	float	step;
}	t_color;

typedef struct s_session
{
	t_point		**source;
	t_vector2	offset;
	int			height;
	int			width;
	float		factor;
	float		angle;
	bool		iso;
	bool		ort;
	void		*mlx_ser;
	void		*mlx_win;
	t_data		mlx_img;
}	t_session;

# define W_WIDTH 1920
# define W_HEIGHT 1080
# define MOD 256

# define BLACK 0x000000
# define RED 0xff4500
# define BLUE 0x191970

# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define PLUS 61
# define MINUS 45
# define SWAP 112
# define ROTATE 114
# define CENTER 99

# define DEG30 0.523599
# define DEG90 1.5708

/*	->PARSE<-	*/
int		ft_atoi(char *str);
int		ft_atohex(const char *str);
int		tab_size(char **array);
void	ft_strlcpy(char *dest, const char *src, size_t size);
void	*clear(char **array);
char	**ft_split(const char *str, char c);
/*	->STRUCT<-	*/
void	build_t_point_grid(t_session *instance, int filein);
void	free_t_points(t_point **grid, int height);
int		check_bounds(t_point *start, t_point *end);
void	offset_for_angle(t_session *instance, t_vector2 *offset);
/*	->INSTANCE<-	*/
int		open_file(t_session *instance, char *argv);
void	mlx_shutdown(t_session *instance);
void	mlx_update(t_session *instance);
int		exit_hook(t_session *instance);
int		handle_key(int keycode, t_session *instance);
void	reset_projection(t_session *instance);
/*	->GRAPHICS<	*/
void	transform_points(t_session *instance, t_point *start, t_point *end);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	put_pixels(t_session *instance, t_point *start, t_point *end);
void	draw_map(t_session *instance);
void	reverse_draw_map(t_session *instance);
/*	->COLOR<-	*/
void	init_color(t_color *color, t_point *start, t_point *end);
void	clear_image(t_session *instance, int color);
int		create_rgb(float ratio, int start, int end);

#endif
