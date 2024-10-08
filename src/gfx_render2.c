/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_render2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:41:36 by thopgood          #+#    #+#             */
/*   Updated: 2024/09/17 15:50:55 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moves_to_img(t_vars *vars)
{
	int	num;
	int	thou;
	int	huns;
	int	tens;
	int	ones;

	num = vars->moves;
	thou = num / 1000;
	huns = (num / 100) % 10;
	tens = (num / 10) % 10;
	ones = num % 10;
	img_to_img(vars->xpm[XTRA_LINE], vars->font[thou], (FSZ * 6), FSZ);
	img_to_img(vars->xpm[XTRA_LINE], vars->font[huns], (FSZ * 7), FSZ);
	img_to_img(vars->xpm[XTRA_LINE], vars->font[tens], (FSZ * 8), FSZ);
	img_to_img(vars->xpm[XTRA_LINE], vars->font[ones], (FSZ * 9), FSZ);
}

/*
 * Renders enemy character on map
 */
void	render_enemies(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map->h)
	{
		x = -1;
		while (++x < vars->map->w)
		{
			if (vars->map->map[y][x] == 'B')
			{
				img_to_img(vars->xpm[BG], vars->xpm[BAD_I1], x * TSZ, y * TSZ);
				vars->b.x = x;
				vars->b.y = y;
			}
		}
	}
}
