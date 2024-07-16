/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/16 01:16:45 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void exit_to_window(t_vars *vars, int dst, int src)
{
	img_to_img(vars->xpm[dst], vars->xpm[FIELD], vars->map->exit_x * TSZ, vars->map->exit_y * TSZ);
	img_to_img(vars->xpm[dst], vars->xpm[CHESTO], vars->map->exit_x * TSZ + 8, vars->map->exit_y * TSZ + 8);
	img_to_img(vars->xpm[dst], vars->xpm[src], vars->map->exit_x * TSZ, vars->map->exit_y * TSZ);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[dst].img_ptr, 0, 0);
}

void chest_animation(t_vars *vars)
{
	if (vars->map->coin_count == 0)
	{
		vars->chest_event = 1;
		vars->map->coin_count = -1;
		vars->frames = vars->loop;
		exit_to_window(vars, BG, SP1);
	}
	if (vars->loop == vars->frames + 500 && vars->chest_event)
		exit_to_window(vars, BG, SP2);
	if (vars->loop == vars->frames + 1000 && vars->chest_event)
		exit_to_window(vars, BG, SP3);
	if (vars->loop == vars->frames + 2000 && vars->chest_event)
		exit_to_window(vars, BG, SP1);
	if (vars->loop == vars->frames + 2500 && vars->chest_event)
	{
		img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->exit_x * TSZ, vars->map->exit_y * TSZ);
		img_to_img(vars->xpm[BG], vars->xpm[CHESTO], vars->map->exit_x * TSZ + 8, vars->map->exit_y * TSZ + 8);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
	}
}

void zombie_to_window(t_vars *vars, int zom_img)
{
	img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->b.x * TSZ, vars->b.y * TSZ);
	img_to_img(vars->xpm[BG], vars->xpm[zom_img], vars->b.x * TSZ, vars->b.y * TSZ);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
}

void idle_zombie(t_vars *vars)
{
	if ((double)(vars->loop % ZOM_SPEED) == (int)ZOM_SPEED / 1.33 /* || vars->loop % ZOM_SPEED == ZOM_SPEED / 1 */)
	{
		moves_possible(vars);
		vars->slash = 1;
	}
	if (vars->loop % ZOM_SPEED == ZOM_SPEED / 2 || vars->loop % ZOM_SPEED == 0) // 0 40k
		vars->slash = 0;
	if (vars->loop % (ZOM_SPEED / 8) == 0 && vars->slash == 0) // 0
		zombie_to_window(vars, BAD_I1);
	if (vars->loop % (ZOM_SPEED / 8) == ZOM_SPEED / 20 && vars->slash == 0) // 2k
		zombie_to_window(vars, BAD_I2);
	if (vars->loop % (ZOM_SPEED / 8) == ZOM_SPEED / 10 && vars->slash == 0) // 4k
		zombie_to_window(vars, BAD_I3);
	if (vars->loop % (ZOM_SPEED / 8) == ZOM_SPEED / 6 && vars->slash == 0) // 6k
		zombie_to_window(vars, BAD_I4);
	if (vars->loop % (ZOM_SPEED / 8) == ZOM_SPEED / 5 && vars->slash == 0) // 8k
		zombie_to_window(vars, BAD_I5);
}

void print_moves(t_vars *vars)
{
	char *moves_str;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[XTRA_LINE].img_ptr, 0, vars->map->h * TSZ);
	mlx_string_put(vars->mlx, vars->win, 10, (vars->map->h + 1) * TSZ - TEXT_H, TEXT_COLOR, "Moves:");
	moves_str = ft_itoa(vars->moves);
	if (moves_str == NULL)
		error_handling_all(ERR_MALLOC, vars);
	mlx_string_put(vars->mlx, vars->win, 50, (vars->map->h + 1) * TSZ - TEXT_H, TEXT_COLOR, moves_str);
	free(moves_str);
}
