/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/16 21:20:35 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	exit_to_window(t_vars *vars, int dst, int src)
{
	img_to_img(vars->xpm[dst], vars->xpm[FIELD], vars->map->exit_x * TSZ,
		vars->map->exit_y * TSZ);
	img_to_img(vars->xpm[dst], vars->xpm[CHESTO], vars->map->exit_x * TSZ + 8,
		vars->map->exit_y * TSZ + 8);
	img_to_img(vars->xpm[dst], vars->xpm[src], vars->map->exit_x * TSZ,
		vars->map->exit_y * TSZ);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[dst].img_ptr, 0, 0);
}

/*
 * Determines rate of chest animatioin
 */
void	chest_animation(t_vars *vars)
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
		img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->exit_x * TSZ,
			vars->map->exit_y * TSZ);
		img_to_img(vars->xpm[BG], vars->xpm[CHESTO], vars->map->exit_x * TSZ
			+ 8, vars->map->exit_y * TSZ + 8);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0,
			0);
	}
}

/*
 * Replaces previous tile and puts zombie image to window
 */
void	zombie_to_window(t_vars *vars, int zom_img)
{
	img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->b.x * TSZ, vars->b.y
		* TSZ);
	img_to_img(vars->xpm[BG], vars->xpm[zom_img], vars->b.x * TSZ, vars->b.y
		* TSZ);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
}

/*
 * Dictates the tempo of the zombie animation.
 */
void	idle_zombie(t_vars *vars)
{
	if (vars->loop % (ZOM_SPEED / 4) == 2)
	{
		moves_possible(vars);
		vars->slash = 1;
	}
	if (vars->loop % (ZOM_SPEED / 4) == 3)
		vars->slash = 0;
	if (vars->loop % (ZOM_SPEED / 8) == 0 && vars->slash == 0)
		zombie_to_window(vars, BAD_I1);
	if (vars->loop % (ZOM_SPEED / 8) == ZOM_SPEED / 20 && vars->slash == 0)
		zombie_to_window(vars, BAD_I2);
	if (vars->loop % (ZOM_SPEED / 8) == ZOM_SPEED / 10 && vars->slash == 0)
		zombie_to_window(vars, BAD_I3);
	if (vars->loop % (ZOM_SPEED / 8) == ZOM_SPEED / 6 && vars->slash == 0)
		zombie_to_window(vars, BAD_I4);
	if (vars->loop % (ZOM_SPEED / 8) == ZOM_SPEED / 5 && vars->slash == 0)
		zombie_to_window(vars, BAD_I5);
}

/*
 * Prints moves to screen
 */
void	print_moves(t_vars *vars)
{
	if (vars->moves <= 9999)
	{
		extra_line(vars);
		moves_to_img(vars);
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->xpm[XTRA_LINE].img_ptr, 0, vars->map->h * TSZ);
	}
}
