
#include "include/fdf.h"

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

