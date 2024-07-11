/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_render_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:29:35 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/11 22:41:22 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	extra_line(t_vars *vars)
{
	int i;
	
	i = -1;
	while (++i < vars->map->w)
		put_img_to_img(vars->xpm[BG], vars->xpm[TATA], i * TILE_SIZE, ((vars->map->h) * TILE_SIZE));
}


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
			put_img_to_img(vars->xpm[BG], vars->xpm[FIELD], x * TILE_SIZE, y
				* TILE_SIZE);
			if (vars->map->map[y][x] == '1')
				put_img_to_img(vars->xpm[BG], vars->xpm[WALL], x * TILE_SIZE, y
					* TILE_SIZE);
			if (vars->map->map[y][x] == 'P')
				put_img_to_img(vars->xpm[BG], vars->xpm[PF], x * TILE_SIZE + 8,
					y * TILE_SIZE + 8);
			if (vars->map->map[y][x] == 'C')
				put_img_to_img(vars->xpm[BG], vars->xpm[COIN], x * TILE_SIZE
					+ 8, y * TILE_SIZE + 8);
			if (vars->map->map[y][x] == 'E')
				put_img_to_img(vars->xpm[BG], vars->xpm[CHESTC], x * TILE_SIZE
					+ 8, y * TILE_SIZE + 8);
		}
	}
}

/*
 * Skips transparent pixels
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
 * Copies one image to another by pixels.
 */
void	put_img_to_img(t_img dst, t_img src, int x, int y)
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
