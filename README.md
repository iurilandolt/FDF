# FDF - Fil de Fer

**FDF** is the first program from the 42 curriculum featuring a graphical interface/window. It renders 3D wireframe images from a file with cartesian coordinates, utilizing the **minilibx** library.

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
 

**Minilibx** works with graphical servers like X-Window, allowing the instantiation of windows and pixel manipulation. While graphical servers in Linux are extensively used in networking, this project doesn't delve into that aspect. However, it's an excellent opportunity to acquaint yourself with concepts like display, window, and image, among others.

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
In regards to parsing, we won't delve into too much detail, but there are some key points to note:

- **The file must exist** (obviously! 😄).
- Our binary must have permission to read the file.
- The file extension must be `.fdf`.
- The file must be readable. Specifically:
  - The number of elements per line must be consistent across all lines, forming a parallelepiped grid.

`.fdf` files come in two variants:
- Standard files with only XYZ information.
- Files with embedded color. 

This means each element of the 2D character map can either be an integer, or an integer followed by a hexadecimal value representing color (e.g., `0` or `0,0xff` respectively).

After parsing, we create a 2D array of `t_point` structs to hold the Cartesian coordinates from our input file.
```c
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		c;
}	t_point;
```
This can easily be achieved with variations of the split, atoi, and get_next_line functions.
```c	
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
		instance->source[i.y] = (t_point *)malloc(sizeof(t_point) * instance->width);
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
```
With our struct ready, we can now begin to display our `t_points` across the window. For this, we need to define a relationship in scale:

- Determine how many `t_points` in the x-axis relate to the window width.
- Determine how many `t_points` in the y-axis relate to the window height.

It's crucial to consider that the window might not be square. Scaling to an aspect ratio that is not 1:1 will distort the shape of our object. For scaling on screens, it's common to use the diagonal of the screen. I implemented something similar:
```c	

	diagonal = hypot(instance->width, instance->height);
	factor = instance->factor * W_HEIGHT / diagonal;
	point->x = round(start->x * factor);
	point->y = round(start->y * factor);
	point->z = round(start->z * instance->factor);
```
After establishing a scale relationship between our map and the window, we need to decide where the first point will be 'printed'. I use a `vector2` variable to divide the screen horizontally and vertically, determining which pixel will represent my `t_point{0,0}`.

You'll likely find that some division ratios are more suitable for specific perspectives, as the size and shape of the volume might change considerably. Experiment with these ratios to find the most visually appealing.
```c	
	instance->offset.x = W_WIDTH * 0.4;
	instance->offset.y = W_HEIGHT * 0.2;
```
At this stage, we have a 2D image representing a top-down, parallel perspective view of our map in the form of a grid. Our objective is to transform this projection into an isometric view. There are several ways to achieve this; theoretically, any viewing angle between 30º and 45º can be considered isometric.

I employed a formula using the cosine and sine functions with a 30º angle to achieve this transformation. This approach effectively alters the 2D grid into an isometric projection.
```c	
	(tmp.x - tmp.y) * cos(DEG30);
	(tmp.x + tmp.y) * sin(DEG30) - tmp->z;
```
For rotation around the z axis you can apply similar logic.
```c	
	tmp.x * cos(instance->angle) - tmp.y * sin(instance->angle);
	tmp.x * sin(instance->angle) + tmp.y * cos(instance->angle);
```
After scaling, converting, rotating, and centering, we need to draw lines between all the points. For this, a line drawing algorithm, such as DDA (Digital Differential Analyzer) or Bresenham, is required. I find DDA easier to implement. Here's a quick rundown of the DDA algorithm:

We'll need reference to

- start & end points (x,y)
```c
current_x = start->x;
current_y = start->y;
 ```
- difference beetween start and end (x,y)
 ```c
delta_x = end->x - start->x;
delta_y = end->y - start->y;
 ``` 
- the number of steps beetween start and end
```c 
step = fmax(fabs(params->delta_x), fabs(params->delta_y)); 
```
- increment size beetween steps (x,y)
```c
x_inc = params->delta_x / params->step;
y_inc = params->delta_y / params->step;
``` 
Knowing this, you can **iterate all steps** between start and end, incrementing `x` and `y` by their corresponding increment values at every iteration. This should allow you to use your `pixel_put` function and 'paint' every pixel between those two pixels, forming a line.
 ```c
current_x += params.x_inc;
current_y += params.y_inc;
 ```  
If you intend to apply color to projections from files without embedded values, you can base the coloration on the image angle or the z-value to achieve gradients. Given that you know the number of 'steps' in a line, this information can be used for **color interpolation** between the start and end colors.

 ```c
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
```
> [Learn about Color in minilibx](https://harm-smits.github.io/42docs/libs/minilibx/colors.html)

With the image drawn, we find ourselves confined within the `mlx_loop()`, lacking interaction capabilities with the image or window – not even the close button. To overcome this limitation, we need to utilize **hooks**.

Hooks act as signal generators and receivers that operate asynchronously to our loop. They enable us to modify values used by the loop or even terminate it. For some useful examples on implementing hooks, check out [this resource](https://harm-smits.github.io/42docs/libs/minilibx/hooks.html).
 ```c
mlx_hook(instance->mlx_win, KeyPress, KeyPressMask, handle_key, instance);
mlx_hook(instance->mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, instance);
mlx_key_hook(instance->mlx_win, handle_key, instance);
```
Every time we change a value in our projection, it's necessary to update the image on our window. This means re-running `draw()` and `mlx_put_image_to_window()`. However, before doing this, we must reset all the pixels in our window to black. If not, the previous image will persist, causing a tearing effect.
 ```c
void	mlx_update(t_session *instance)
{
	float	angle;

	clear_image(instance, BLACK);
	draw_map(instance);
	mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
}
 ```
To properly end the loop and shut down the graphical server, it's crucial to close the program immediately after ending the loop to avoid segmentation faults. The `mlx` library provides specific functions for this purpose. Additionally, addressing any allocated memory at this point is essential.
 ```c
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
 ```
Congratulations you made it to the end of this boring readme file.
Have a great day.
