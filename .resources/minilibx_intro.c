
#include "fdf.h"

#define WIDTH 1280
#define HEIGHT 720

int	main()
{
	void	*mlx_server;
	void	*mlx_win;

	mlx_server = mlx_init();
	mlx_win = mlx_new_window(mlx_server, WIDTH, HEIGHT, "Untitled Window");

	draw_circle(mlx_server, mlx_win, WIDTH / 2, HEIGHT / 2, 250);
	draw_rectangle(mlx_server, mlx_win, WIDTH, HEIGHT);
	mlx_string_put(mlx_server, mlx_win, WIDTH * 0.8, HEIGHT * 0.95, rand() % 0x1000000, "Bananas");
	mlx_loop(mlx_server);
}

void exec_dda(t_session *instance, t_dda *params, t_color *color, int step_count)
{
	float step_ratio;
	int pixel_color;

	if (step_count > params->step)
		return ;
	step_ratio = (float)step_count / params->step;
	pixel_color = create_rgb(step_ratio, color->start, color->end);
	my_mlx_pixel_put(&instance->mlx_img,
		round(params->current_x), round(params->current_y), pixel_color);
	params->current_x += params->x_inc;
	params->current_y += params->y_inc;
	exec_dda(instance, params, color, step_count + 1);
}

void put_pixels(t_session *instance, t_point *start, t_point *end)
{
	t_dda params;
	t_color color;

	init_dda(&params, start, end);
	init_color(&color, start, end);
	exec_dda(instance, &params, &color, 0);
}


void draw_map_recursive(t_session *instance, int x, int y) {
	if (y >= instance->height)
		return;

	if (x < instance->width - 1)
		draw_lines(instance, x, y, 0);
	if (y < instance->height - 1)
		draw_lines(instance, x, y, 1);
	if (x < instance->width - 1)
		draw_map_recursive(instance, x + 1, y);
	else
		draw_map_recursive(instance, 0, y + 1);
}

void draw_map(t_session *instance) {
    draw_map_recursive(instance, 0, 0);
}

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
