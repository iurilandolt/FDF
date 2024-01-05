
#include "fdf.h"

#define WIDTH 1280
#define HEIGHT 720


void draw_circle(void *mlx_server, void *mlx_win, int cx, int cy, int radius)
{
	for (int y = cy - radius; y <= cy + radius; ++y)
	{
		for (int x = cx - radius; x <= cx + radius; ++x)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius)
			{
				mlx_pixel_put(mlx_server, mlx_win, x, y, rand() % 0x1000000);
			}
		}
	}
}

void draw_rectangle(void *mlx_server, void *mlx_win, int width, int height)
{
	for (int y = HEIGHT * 0.1; y < height * 0.9; ++y)
	{
		for (int x = WIDTH * 0.1; x < width * 0.9; ++x)
		{
			mlx_pixel_put(mlx_server, mlx_win, x, y, rand() % 0x1000000);
		}
	}
}

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
