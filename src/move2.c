/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:32:55 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/12 20:06:17 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Moves character, replacing previous tile.
 */
void	move(t_vars *vars, int img, int x, int y)
{
	img_to_img(vars->xpm[BG], vars->xpm[img], ((vars->map->p_x + x)
			* TSZ) + 8, ((vars->map->p_y + y) * TSZ) + 8);
	img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->p_x * TSZ,
		vars->map->p_y * TSZ);
	if (vars->map->p_x == vars->map->exit_x
		&& vars->map->p_y == vars->map->exit_y)
		img_to_img(vars->xpm[BG], vars->xpm[CHESTC], (vars->map->p_x
				* TSZ) + 8, (vars->map->p_y * TSZ) + 8);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
	if (vars->map->map[vars->map->p_y + y][vars->map->p_x + x] == 'C')
	{
		vars->map->coin_count -= 1;
		vars->map->map[vars->map->p_y + y][vars->map->p_x + x] = '0';
	}
	vars->map->p_x += x;
	vars->map->p_y += y;
	ft_printf("Moves: %d\n", ++(vars->moves));
}

/*
 * Turns character in place if movement direction is blocked.
 */
void	turn(t_vars *vars, int img)
{
	if (vars->map->map[vars->map->p_y][vars->map->p_x] == 'E')
		img_to_img(vars->xpm[BG], vars->xpm[CHESTC], vars->map->p_x
			* TSZ + 8, vars->map->p_y * TSZ + 8);
	else
		img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->p_x
			* TSZ, vars->map->p_y * TSZ);
	img_to_img(vars->xpm[BG], vars->xpm[img], ((vars->map->p_x) * TSZ)
		+ 8, ((vars->map->p_y) * TSZ) + 8);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
}
