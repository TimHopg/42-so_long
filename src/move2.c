/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:32:55 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/11 10:33:18 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(t_vars *vars, int img, int x, int y)
{
	put_img_to_img(vars->xpm[BG], vars->xpm[img], ((vars->map->p_x + x)
			* TILE_SIZE) + 8, ((vars->map->p_y + y) * TILE_SIZE) + 8);
	put_img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->p_x * TILE_SIZE,
		vars->map->p_y * TILE_SIZE);
	if (vars->map->p_x == vars->map->exit_x
		&& vars->map->p_y == vars->map->exit_y)
		put_img_to_img(vars->xpm[BG], vars->xpm[CHESTC], (vars->map->p_x
				* TILE_SIZE) + 8, (vars->map->p_y * TILE_SIZE) + 8);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
	if (vars->map->map[vars->map->p_y + y][vars->map->p_x + x] == 'C')
	{
		vars->map->coin_count -= 1;
		vars->map->map[vars->map->p_y + y][vars->map->p_x + x] = '0';
	}
	vars->map->p_x += x;
	vars->map->p_y += y;
}

void	turn(t_vars *vars, int img)
{
	if (vars->map->map[vars->map->p_y][vars->map->p_x] == 'E')
		put_img_to_img(vars->xpm[BG], vars->xpm[CHESTC], vars->map->p_x
			* TILE_SIZE + 8, vars->map->p_y * TILE_SIZE + 8);
	else
		put_img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->p_x
			* TILE_SIZE, vars->map->p_y * TILE_SIZE);
	put_img_to_img(vars->xpm[BG], vars->xpm[img], ((vars->map->p_x) * TILE_SIZE)
		+ 8, ((vars->map->p_y) * TILE_SIZE) + 8);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
}
