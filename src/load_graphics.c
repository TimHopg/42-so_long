/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:50:37 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/08 13:30:45 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define BG 0
#define FIELD 1
#define WALL 2
#define COIN 3
#define PF 4
#define CHESTC 5
#define CHESTO 6

void put_pixel_img(t_img img, int x, int y, int color);

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

t_img new_file_img(char *path, t_vars *vars)
{
    t_img image;

    image.img_ptr = mlx_xpm_file_to_image(vars->mlx, path, &image.w, &image.h);
    image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp), &(image.line_len), &(image.endian));
    return (image);
}

void put_pixel_img(t_img img, int x, int y, int color)
{
    char *dst;

    if (color == (int)0xFF000000)
        return;
    if (x >= 0 && y >= 0 && x < img.w && y < img.h)
    {
        dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void load_gfx(t_vars *vars)
{
    // ft_bzero(vars->xpm, sizeof(t_img) * 5);
    vars->xpm[BG] = new_img(vars->map->w * TILE_SIZE, vars->map->h * TILE_SIZE, vars);
    vars->xpm[FIELD] = new_file_img("gfx/field.xpm", vars);
    vars->xpm[WALL] = new_file_img("gfx/wall.xpm", vars);
    vars->xpm[COIN] = new_file_img("gfx/coin.xpm", vars);
    vars->xpm[PF] = new_file_img("gfx/pf.xpm", vars);
    vars->xpm[CHESTC] = new_file_img("gfx/chestc.xpm", vars);
    if (!(vars->xpm[BG].img_ptr) || !(vars->xpm[FIELD].img_ptr) || !(vars->xpm[WALL].img_ptr) || !(vars->xpm[PF].img_ptr) || !(vars->xpm[COIN].img_ptr) || !(vars->xpm[CHESTC].img_ptr))
        error_handling_all(ERR_MALLOC, vars);
    // malloc checks
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
            put_img_to_img(vars->xpm[BG], vars->xpm[FIELD], x * TILE_SIZE, y * TILE_SIZE);
            if (vars->map->map[y][x] == '1')
                put_img_to_img(vars->xpm[BG], vars->xpm[WALL], x * TILE_SIZE, y * TILE_SIZE);
            if (vars->map->map[y][x] == 'P')
                put_img_to_img(vars->xpm[BG], vars->xpm[PF], x * TILE_SIZE + 8, y * TILE_SIZE + 8);
            if (vars->map->map[y][x] == 'C')
                put_img_to_img(vars->xpm[BG], vars->xpm[COIN], x * TILE_SIZE + 8, y * TILE_SIZE + 8);
            if (vars->map->map[y][x] == 'E')
                put_img_to_img(vars->xpm[BG], vars->xpm[CHESTC], x * TILE_SIZE + 8, y * TILE_SIZE + 8);
            x++;
        }
        y++;
    }
}

void load_background(t_vars *vars)
{

    load_gfx(vars);
    render_map(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
}
