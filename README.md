# fdf  - fil de fer

fdf is the first program from the 42 curriculum that has a graphical interface/window.
it renders 3D wireframe images from a file with cartesian coordinates using the minilibx library.

-> https://harm-smits.github.io/42docs/libs/minilibx

this project complies with the 42 Network norms.

no for loops.

no declarations/initializations on control structures.

functions have a max of 5 arguments and a total of 25 lines and 80 tokens.
maximum 5 functions per file.
no functions from any libray except for,

open() / close() / read / write / malloc / free
perror / strerror / exit
anything from math.h

minilibx wworks with a graphical server like X-Window and allows us to instanciate a window and manipulate the pixels inside it.
graphical servers in linux have a much extensivier use around network but we do not explore this in this project.
it is however a good ideia to get familiar with the concepts of display, window and image among other things.

-> https://www.techopedia.com/definition/10101/x-window-system

it is mandatory to use a specific struct given to us by the library documentation;

	typedef struct s_data
	{
		void	*img;
		char	*addr;
		int	bits_per_pixel;
		int	line_length;
		int	endian;
	}		t_data;
 
this holds pointers to where the image we draw is stored and also to where each pixels information is stored before we push the image to the window;

with this library we can write the pixel values and coordinates to be stored in a linear character array, 
the library handles the arithmetic to know where each pixel goes where, where each line ends and a new one begins etc.

this method as opposite to changing the pixels directly in the window without waiting for the next frame, wich is really slow, is a lot more efficient,
and allows us to push a complete image to the window in a single frame, here is an example of a function that allows us to write the image to a t_data structure and then
use the minilibx libary function: mlx_put_image_to_window() to instantly push the iamge to the window.

	void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
	{
		char	*dst;
	
		if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
			return ;
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}

	mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);

to initialize the graphical server and assign a window to it there is a series of steps we must take.
here is an example of a startup sequence; 

iniitate graphical server, 

alloc new window, alloc new image, 

set values and pointers for the t_data struct, 

keep the window open.

 	void	mlx_startup(t_session *instance)
	{
		instance->mlx_ser = mlx_init();
		instance->mlx_win = mlx_new_window(instance->mlx_ser, W_WIDTH, W_HEIGHT, "42 FDF");
		instance->mlx_img.img = mlx_new_image(instance->mlx_ser, W_WIDTH, W_HEIGHT);
		instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img, 
				&instance->mlx_img.bits_per_pixel, &instance->mlx_img.line_length,
				&instance->mlx_img.endian);
		if (!instance->mlx_ser || !instance->mlx_win || !instance->mlx_img.img)
			mlx_shutdown(instance);
	}

to keep the window open we use;

	mlx_loop(instance->mlx_ser);

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
 so each element of the 2D character map can either be an int, or an int follow by a hex value representing color.
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
for scaling in screens it is common to use the diagonal of the screen, i did something similar;

	diagonal = hypot(instance->width, instance->height);
	factor = instance->factor * W_HEIGHT / diagonal;
	point->x = round(start->x * factor);
	point->y = round(start->y * factor);
	point->z = round(start->z * instance->factor);

after setting a relation of scale beetween our map and the window we need to decide where the first point will be printed.
i use a vector2 variable to devide the screen horizontaly and verticaly and decide wich pixel will be my t_point{0,0}.
you'll most likely find some division ratios more adequate for particular perspectives since the size and shape of the volume might change considerably.

	instance->offset.x = W_WIDTH * 0.4;
	instance->offset.y = W_HEIGHT * 0.2;

at this point we only have a 2D image, a top down, paralel perspective view of our map in the shape of a grid.
our goal is to convert this projection to isometric, there a couple of ways to achieve this, in theory any viewing angle beetween 30º and 45º can be considered isometric.
i used a formula with the cosine and sine functions on a 30º value.

	(tmp.x - tmp.y) * cos(DEG30);
	(tmp.x + tmp.y) * sin(DEG30) - tmp->z;

for rotation around the z axis you can apply similar logic

	tmp.x * cos(instance->angle) - tmp.y * sin(instance->angle);
	tmp.x * sin(instance->angle) + tmp.y * cos(instance->angle);

after that we use a line drawing algorightm, DDA, to print all the horizontal and vertical lines beetween points, starting at 0,0.

explain DDA logic.

during the application of the DDA algo we also apply color,
in the case that the read file has no color values, we will give a color value based on the Z value of each point.
then using the number of steps necessaery to draw each line, we set a ratio of color to be applied to each pixel on the line, starting with the color of the start point, and ending in the color of the end point.
with each step we blend the color value from the start color to the end color.

explain zoom, translation and rotation


explain the minilibx libary, startup, update and shutdown functions.
