/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_render2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:41:36 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/16 12:37:05 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Renders moves text
 */
void render_text(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, 10, (vars->map->h + 1) * TSZ - TEXT_H, TEXT_COLOR, "Moves:");
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
