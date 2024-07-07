/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:50:37 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/07 21:26:37 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define BG 0
#define FIELD 1
#define WALL 2

void	put_pixel_img(t_img img, int x, int y, int color);

// void render_map(void *mlx, void *win, void *tiles[])
// {
//     for (int y = 0; y < MAP_HEIGHT; y++) {
//         for (int x = 0; x < MAP_WIDTH; x++) {
//             int tile_type = map[y][x];
//             mlx_put_image_to_window(mlx, win, tiles[tile_type], x * TILE_SIZE, y * TILE_SIZE);
//         }
//     }
// }

unsigned int get_pixel_img(t_img img, int x, int y)
{
    return (*(unsigned int *)((img.addr + (y * img.line_len) + (x * img.bpp / 8))));
}

void put_img_to_img(t_img dst, t_img src, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i < src.w)
    {
        j = 0;
        while (j < src.h)
        {
            put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
            j++;
        }
        i++;
    }
}

t_img new_img(int w, int h, t_vars *vars)
{
    t_img image;

    image.img_ptr = mlx_new_image(vars->mlx, w, h);
    image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
                                   &(image.line_len), &(image.endian));
    image.w = w;
    image.h = h;
    return (image);
}

t_img	new_file_img(char * path, t_vars *vars) {
	t_img image;

	image.img_ptr = mlx_xpm_file_to_image(vars->mlx, path, &image.w, &image.h);
    image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp), &(image.line_len), &(image.endian));
	return (image);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h) {
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void render_map(t_vars *vars)
{
    int x;
    int y;

    y = 0;
    while (y < vars->map->h)
    {
        x = 0;
        while (x < vars->map->w)
        {
            if (vars->map->map[y][x] == '0')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->gfx[FIELD], x * TILE_SIZE, y * TILE_SIZE);
            if (vars->map->map[y][x] == '1')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->gfx[WALL], x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}



// void create_bg(t_vars *vars)
// {
//     int i;

//     i = 0;
//     vars->bg = malloc(vars->map->w * vars->map->h * sizeof(int));
//     if (vars->bg == NULL)
//         exit(0); //
//     while (i < vars->map->w * vars->map->h)
//     {
//         vars->bg[i] = 0xFF0000; // Red background color (ARGB format)
//     }
// }

void load_xpm(t_vars *vars)
{
    int img_size;

    img_size = TILE_SIZE;
    // create_bg(vars);
    // mlx_set_window_bg_img(vars->win, vars->bg, vars->map->w, vars->map->h);
    // mlx_put_image_to_window(vars->mlx, vars->mlx, vars->bg, vars->map->w, vars->map->h);

    vars->gfx[1] = mlx_xpm_file_to_image(vars->mlx, "gfx/field.xpm", &img_size, &img_size);
    vars->gfx[2] = mlx_xpm_file_to_image(vars->mlx, "gfx/wall.xpm", &img_size, &img_size);
    render_map(vars);
}

void load_background(t_vars *vars)
{
    t_img base_image;
    t_img bg;
    t_img ring;

    base_image = new_img(vars->map->w * TILE_SIZE, vars->map->h * TILE_SIZE, vars);
    {
        bg = new_file_img("gfx/field.xpm", vars);
        if (!bg.img_ptr)
            exit (2); // !
        put_img_to_img(base_image, bg, 0, 0);
    }
    {
        ring = new_file_img("gfx/wall.xpm", vars);
        if (!ring.img_ptr)
            exit (2); // !
        put_img_to_img(base_image, ring, 0, 0);
    }
    mlx_put_image_to_window(vars->mlx, vars->win, base_image.img_ptr, 0, 0);
}