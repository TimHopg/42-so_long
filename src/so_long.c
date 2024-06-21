/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:57:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/21 18:31:37 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <math.h>

int			interpolate(int color1, int color2, float factor);

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void *mlx;
	void *win;
}			t_vars;

int close_window (int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	else
		return (0);
	free(vars->mlx);
	exit(0);
	// return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		my_mlx_pixel_put(data, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_rectangle(t_data *data, int x, int y, int width, int height,
		int colour)
{
	int	i;
	int	j;

	i = y;
	while (i < y + height)
	{
		j = x;
		while (j < x + width)
			my_mlx_pixel_put(data, j++, i, colour);
		i++;
	}
}

void	draw_circle(t_data *data, int x0, int y0, int radius, int color)
{
	int	x;
	int	y;
	int	err;

	x = radius;
	y = 0;
	err = 0;
	while (x >= y)
	{
		my_mlx_pixel_put(data, x0 + x, y0 + y, color);
		my_mlx_pixel_put(data, x0 + y, y0 + x, color);
		my_mlx_pixel_put(data, x0 - y, y0 + x, color);
		my_mlx_pixel_put(data, x0 - x, y0 + y, color);
		my_mlx_pixel_put(data, x0 - x, y0 - y, color);
		my_mlx_pixel_put(data, x0 - y, y0 - x, color);
		my_mlx_pixel_put(data, x0 + y, y0 - x, color);
		my_mlx_pixel_put(data, x0 + x, y0 - y, color);
		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void	draw_gradient(t_data *data, int x, int y, int width, int height,
		int color1, int color2)
{
	float	factor;
	int		color;

	for (int i = 0; i < height; i++)
	{
		factor = (float)i / height;
		color = interpolate(color1, color2, factor);
		draw_rectangle(data, x, y + i, width, 1, color);
	}
}

int	interpolate(int color1, int color2, float factor)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(((color1 >> 16) & 0xFF) * (1 - factor) + ((color2 >> 16) & 0xFF)
			* factor);
	green = (int)(((color1 >> 8) & 0xFF) * (1 - factor) + ((color2 >> 8) & 0xFF)
			* factor);
	blue = (int)((color1 & 0xFF) * (1 - factor) + (color2 & 0xFF) * factor);
	return ((red << 16) | (green << 8) | blue);
}

int	main(void)
{
	t_data	img;
	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Thanks For All The Fish!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FFaa00);
	draw_line(&img, 100, 100, 500, 500, 0x00FF00);
	draw_rectangle(&img, 1200, 300, 400, 600, 0x00882000);
	draw_circle(&img, 400, 400, 50, 0x00FF0082);
	draw_gradient(&img, 800, 100, 200, 200, 0xFF0000, 0x000000FF);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, close_window, &vars);
	mlx_loop(vars.mlx);
}

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
// 	mlx_loop(mlx);
// }
