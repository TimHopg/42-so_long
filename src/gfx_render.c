/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:29:35 by thopgood          #+#    #+#             */
/*   Updated: 2024/09/17 15:50:50 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Renders extra line at bottom of map to display score.
 */
void	extra_line(t_vars *vars)
{
	int	x;

	x = -1;
	while (++x < vars->map->w)
		img_to_img(vars->xpm[XTRA_LINE], vars->xpm[TATA], x * TSZ, 0);
	img_to_img(vars->xpm[XTRA_LINE], vars->font[MOVES], FSZ / 2, FSZ);
}

/*
 * Renders map based on map file icons.
 */
void	render_map(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map->h)
	{
		x = -1;
		while (++x < vars->map->w)
		{
			img_to_img(vars->xpm[BG], vars->xpm[FIELD], x * TSZ, y * TSZ);
			if (vars->map->map[y][x] == '1')
				img_to_img(vars->xpm[BG], vars->xpm[WALL], x * TSZ, y * TSZ);
			if (vars->map->map[y][x] == 'P')
				img_to_img(vars->xpm[BG], vars->xpm[PF], x * TSZ + 8, y * TSZ
					+ 8);
			if (vars->map->map[y][x] == 'C')
				img_to_img(vars->xpm[BG], vars->xpm[COIN], x * TSZ + 8, y * TSZ
					+ 8);
			if (vars->map->map[y][x] == 'E')
				img_to_img(vars->xpm[BG], vars->xpm[CHESTC], x * TSZ + 8, y
					* TSZ + 8);
		}
	}
}

/*
 * Puts pixel 'colour' to img at coords (x,y). Skips transparent pixel
 */
void	put_pixel_img(t_img img, int x, int y, int colour)
{
	char	*dst;

	if (colour == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *)dst = colour;
	}
}

/*
 * Copies one image to another by pixel.
 */
void	img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < src.w)
	{
		j = -1;
		while (++j < src.h)
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
	}
}

/*
 * Fetches specific pixel from img at (x,y) coords.
 */
unsigned int	get_pixel_img(t_img img, int x, int y)
{
	unsigned int	pixel;

	pixel = *((unsigned int *)(img.addr + (y * img.line_len) + (x * img.bpp
					/ 8)));
	return (pixel);
}
