# fdf - fil de fer

**fdf** is the first program from the 42 curriculum featuring a graphical interface/window. It renders 3D wireframe images from a file with cartesian coordinates, utilizing the **minilibx** library.

> [Learn more about minilibx](https://harm-smits.github.io/42docs/libs/minilibx)

<sub>_This project follows the 42 norm:_</sub>

<sub>- _No for loops._</sub>

<sub>- _No declarations/initializations in control structures._</sub>

<sub>- _Functions are limited to a max of 5 arguments, 25 lines, and 80 tokens._</sub>

<sub>- _A maximum of 5 functions per file._</sub>

<sub>- _Use of only specific library functions:_</sub>

 <sub> - _`open()`, `close()`, `read`, `write`, `malloc`, `free`_</sub>
 
 <sub> - _`perror`, `strerror`, `exit`_</sub>
 
 <sub> - _Any function from `math.h`_</sub>
 

**minilibx** works with graphical servers like X-Window, allowing the instantiation of windows and pixel manipulation. While graphical servers in Linux are extensively used in networking, this project doesn't delve into that aspect. However, it's an excellent opportunity to acquaint yourself with concepts like display, window, and image, among others.

> [Learn about X-Window System](https://www.techopedia.com/definition/10101/x-window-system)


It is mandatory to use a specific struct given to us by the library documentation:
```c
typedef struct s_data
{
    void	*img;
    char	*addr;
    int	bits_per_pixel;
    int	line_length;
    int	endian;
}		t_data;	
```
This holds pointers to where the image we draw is stored and also to where each pixel's information is stored before we push the image to the window.

With this library, we can write the pixel values and coordinates to be stored in a linear character array. The library has functions that handle the arithmetic of where each pixel goes, where each line ends and a new one begins, etc.

This method, as opposed to changing the pixels directly in the window without waiting for the next frame, which is really slow, is a lot more efficient. It allows us to push a complete image to the window in a single frame. Here is an example of a function that allows us to write the image to a `t_data` structure and then use the minilibx library function mlx_put_image_to_window() to instantly push the image to the window.
```c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
```

To initialize the graphical server and assign a window to it, there is a series of steps we must take. Here is an example of a startup sequence:

1. Initiate graphical server
2. Allocate new window
3. Allocate new image
4. Set values and pointers for the `t_data` struct
5. Keep the window open
```c
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
```
to keep the window open we use;

	mlx_loop(instance->mlx_ser);

Due to norm compliance, this project relies extensively on structs. This approach allows us to hold a lot of information regarding various aspects of our application, such as:

- Variables of our client
- Graphical server window
- The state of the image
- The state of the 3D volume we are representing

Additionally, it includes other elements like color, vectors, drawing algorithm parameters and anything we might need to have access to later when we try to interact with the image during runtime. 
Utilizing structs is also a cheeky way not to waste lines/columns with variable initializations/declarations.

```c
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
```
in regards to parsing we wont go into much detail, however there are some key points;

the file must exist :D

our binary must have permision to read the file.

the file extension must be '.fdf'

the file must be readable, i.e; 

the number of elements per line must be the same for every line. the grid is a paralelipipede.

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

	
	void	set_t_point_values(t_point *point, int x, int y, char *tab)
	{
		char		**color;
	
		color = ft_split(tab, ',');
		point->x = x;
		point->y = y;
		point->z = ft_atoi(tab);
		point->c = 0;
		if (color[1])
			point->c = ft_atohex(color[1]);
		clear(color);
	}

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

after scaling, converting, rotating and centering we need to draw lines beetween all the points.
for that you'll need to implement a line drawing algorithm, such as DDA or Bresenham.
i find DDA easier to implement, here is a quick run down

we'll need reference to

start & end points (x,y)

	current_x = start->x;
	current_y = start->y;
 
difference beetween start and end (x,y)
 
 	delta_x = end->x - start->x;
	delta_y = end->y - start->y;
 
 the number of steps beetween start and end
   
	step = fmax(fabs(params->delta_x), fabs(params->delta_y)); 
 
 increment size beetween steps (x,y)
 
	x_inc = params->delta_x / params->step;
	y_inc = params->delta_y / params->step;
 
knowing this you can iterate all steps beetween start and end incrementing x and y by their corresponding increment values at every iteration,
this should allow you to use your pixel_put function and 'paint' every pixel beetween those two pixels forming a line.

	current_x += params.x_inc;
	current_y += params.y_inc;
   
if you intend to apply color to the projections whose files do not bring any embebed values, you can do that based on the image angle, or the z value achieving gradients.
since you know the number of 'steps' in a line, you can use that value to implement some kind of interpolation beetween the start and the end color.

		while (i <= params.step)
			color.step = i / params.step;
			pixel_color = create_rgb(color.step, color.start, color.end);

	int	create_rgb(float ratio, int start, int end)
	{
		int	r;
		int	g;
		int	b;
	
		r = interpolate(ratio, (start >> 16) & 0xFF, (end >> 16) & 0xFF);
		g = interpolate(ratio, (start >> 8) & 0xFF, (end >> 8) & 0xFF);
		b = interpolate(ratio, start & 0xFF, end & 0xFF);
		return ((r << 16) | (g << 8) | b);
	}
 
with the image drawn we are stuck in the mlx_loop(), there is no way to interact with the image or with the window, not even the close button.
for this we need to use 'hooks'

hooks are basically signal generators and recievers that will work asyncronous to our loop, allowing us to change values being used by the loop or even ending it.
-> https://harm-smits.github.io/42docs/libs/minilibx/hooks.html <- here are a few usefull examples.

	mlx_hook(instance->mlx_win, KeyPress, KeyPressMask, handle_key, instance);
	mlx_hook(instance->mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, instance);
   	mlx_key_hook(instance->mlx_win, handle_key, instance);

to properly end the loop and shutdown the graphical server we should have in account that we must close the program imidiatly after ending the loop in order not to get any segfaults.
the mlx library has specific functions to deal with this, allocated memory should also be addressed at this point.

	void	mlx_shutdown(t_session *instance)
	{
		mlx_loop_end(instance->mlx_ser);
		if (instance->mlx_img.img)
			mlx_destroy_image(instance->mlx_ser, instance->mlx_img.img);
		if (instance->mlx_win)
		{
			mlx_destroy_window(instance->mlx_ser, instance->mlx_win);
			instance->mlx_win = NULL;
		}
		if (instance->mlx_ser)
		{
			mlx_destroy_display(instance->mlx_ser);
			free(instance->mlx_ser);
		}
		free_t_points(instance->source, instance->height);
		free(instance);
		exit(0);
	}
