/*

int		**alloc_2d_grid(int width, int height)
{
	int **grid;
	int y;
	int x;

	grid = (int **)malloc(sizeof(int *) * height);
    y = 0;
	while (y < height)
	{
		grid[y] = (int *)malloc(sizeof(int) * width);
		x = 0;
		while (x < width)
		{
			grid[y][x] = 0;
			x++;
		}
		y++;
	}
	return(grid);
}

void	free_2d_grid(int **grid, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{

		free(grid[y]);
		y++;
	}
	free(grid);
}

void	print_2d_grid(int **grid, int height, int width)
{
	int y, x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("%-3d ", grid[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}

void	gen_2d_source(t_session *instance, int filein)
{
	char		*line;
	char		**tab;
	t_vector2	i;

	i.y = 0;
	instance->source = (int**)malloc(sizeof(int *) * instance->height);
	while ((line = get_next_line(filein)) && i.y < instance->height)
	{
		i.x = 0;
		tab = ft_split(line, ' ');
		instance->width = tab_size(tab);
		instance->source[i.y] =  (int *)malloc(sizeof(int) * instance->width);
		while (tab[i.x] && i.x < instance->width)
		{
			instance->source[i.y][i.x] = ft_atoi(tab[i.x]);
			i.x++;
		}
		clear(tab);
		free(line);
		i.y++;
	}
	print_2d_grid(instance->source, instance->height, instance->width);
}

void	isometric_transform(t_session *instance)
{
	t_transform	new;
	t_vector2	i;
	double		z;

	instance->projection = (int**)malloc(sizeof(int *) * instance->height);
	new.angle = 45.0;
	new.radian_angle = new.angle * M_PI / 180.0;
	i.y = 0;
	while (i.y < instance->height)
	{
		i.x = 0;
		instance->projection[i.y] =  (int *)malloc(sizeof(int) * instance->width);
		while (i.x < instance->width)
		{
			z = instance->source[i.y][i.x];
			new.x = z * cos(new.radian_angle);
			new.y = z * sin(new.radian_angle);
			instance->projection[i.y][i.x] = (int)new.x;
			i.x++;
		}
		i.y++;
	}
	print_2d_grid(instance->projection, instance->height, instance->width);
}

//draw_circle(&instance->mlx_img, WIDTH / 2, HEIGHT /2, 500, 0x00FF0000);
void draw_circle(t_data *data, int cx, int cy, int radius, int color)
{
	for (int y = cy - radius; y <= cy + radius; ++y)
	{
		for (int x = cx - radius; x <= cx + radius; ++x)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius)
			{
				my_mlx_pixel_put(data, x, y, color);
			}
		}
	}
}

void draw_rectangle(t_data *data, int height, int width, int color)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}

void draw_array_cells(t_data *data, int **array, int rows, int cols)
{
	int width = W_WIDTH / cols;   // Calculate width of each rectangle
	int height = W_HEIGHT / rows; // Calculate height of each rectangle

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < cols; ++x)
		{
			int color = array[y][x] * 10;
			int startX = x * width;
			int startY = y * height;

			// Draw a point for each cell // d stands for displacement
			for (int dy = 0; dy < height; ++dy)
			{
				for (int dx = 0; dx < width; ++dx)
				{
					my_mlx_pixel_put(data, startX + dx, startY + dy, color);
				}
			}
		}
	}
}

void draw_array_points(t_data *data, int **array, int rows, int cols)
{
	// Calculate the size of each square
	int dx = W_WIDTH / cols;
	int dy = W_HEIGHT / rows;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int color = array[i][j] * 25;
			int x_center = j * dx + dx / 2; // Calculate the center x-coordinate
			int y_center = i * dy + dy / 2; // Calculate the center y-coordinate

			// Draw a single point for each cell
			my_mlx_pixel_put(data, y_center, x_center, color);
		}
	}
}

*/
