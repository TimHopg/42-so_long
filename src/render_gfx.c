/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gfx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:29:35 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/11 10:38:01 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->map->h)
	{
		x = 0;
		while (x < vars->map->w)
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
			x++;
		}
		y++;
	}
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

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
