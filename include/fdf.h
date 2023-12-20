/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:20:03 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/20 20:46:45 by rlandolt         ###   ########.fr       */
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

#endif
