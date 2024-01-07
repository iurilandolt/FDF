# fdf  - fil de fer

fdf is a program that generates 3D wireframe images from 2D character maps with cartesian coordinates.

this project complies with the 42 Network norms.

no for loops,
no declarations/initializations on control structures;
functions have a max of 5 arguments and a total of 25 lines, 80 colums.
maximum 5 functions per file.
no functions from any libray except for,
	open() / close() / read / write / malloc / free
	perror / strerror / exit
	anything from math.h

etc.

understanding windows / graphical servers X11 / small intro.

	typedef struct s_data
	{
		void	*img;
		char	*addr;
		int	bits_per_pixel;
		int	line_length;
		int	endian;
	}		t_data;

	void	mlx_startup(t_session *instance)
	{
		instance->mlx_ser = mlx_init();
		instance->mlx_win = mlx_new_window(instance->mlx_ser,
				W_WIDTH, W_HEIGHT, "42 FDF");
		instance->mlx_img.img = mlx_new_image(instance->mlx_ser, W_WIDTH, W_HEIGHT);
		instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img, 
				&instance->mlx_img.bits_per_pixel, &instance->mlx_img.line_length,
				&instance->mlx_img.endian);
		if (!instance->mlx_ser || !instance->mlx_win || !instance->mlx_img.img)
			mlx_shutdown(instance);
	}

	mlx_loop(instance->mlx_ser);
 
waiting for next frame / drawing pixels

	void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
	{
		char	*dst;
	
		if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
			return ;
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}

	mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);

Due to norm compliance this project relies extensinvely in structs.
This will allows us to hold a lot of information regarding the constant variables of our client, graphical server window, the state of the image, and the state of the 3D volume we are representing, among other things like color, vectors, drawing algorithm paramaters etc.
It is also a cheaky way not to waste lines/colums with variable initializations/declarations.

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

in regards to parsing we wont go into much detail, however there are some key points;
the file must exist :D
our binary must have permision to read the file.
the file extension must be '.fdf'
the file must be readable, i.e; 
	the number of elements per line must be the same for every line.
 	the grid is a paralelipipede

.fdf files have two variants, standard files with only XYZ information, and files with embebed color.
 so each element of the 2D character map can either be an int, or an int follow by a hex value.
 so either '0' or '0,0xff respectively' 
  
after this we create a 2D array of t_point structs that will hold the cartesian coordinates from our input file.

	typedef struct s_point
	{
		int		x;
		int		y;
		int		z;
		int		c;
	}	t_point;

you can easily achieve this with variations of the split, atoi, and get_next_line functions.

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

with our struct ready we can now start to print our t_points across the window.
for this we must define a relationship in scale, how many t_points in the x axis do we have in relation to the window width,
and how many in the y axis in relation to the window height.
we also need to consider that the window might not be a square, and that scaling to an aspect ratio that is not 1:1 will distort the shape of our object.

	diagonal = hypot(instance->width, instance->height);
	factor = instance->factor * W_HEIGHT / diagonal;
	point->x = round(start->x * factor);
	point->y = round(start->y * factor);
	point->z = round(start->z * instance->factor);

explain conversion, scaling and centering.

after that we use a line drawing algorightm, DDA, to print all the horizontal and vertical lines beetween points, starting at 0,0.

explain DDA logic.

during the application of the DDA algo we also apply color,
in the case that the read file has no color values, we will give a color value based on the Z value of each point.
then using the number of steps necessaery to draw each line, we set a ratio of color to be applied to each pixel on the line, starting with the color of the start point, and ending in the color of the end point.
with each step we blend the color value from the start color to the end color.

explain zoom, translation and rotation


explain the minilibx libary, startup, update and shutdown functions.
