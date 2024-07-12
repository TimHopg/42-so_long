/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:55:59 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/12 17:57:52 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Initiates the hooks and loops necessary for the game to run.
 */
void	run_game(t_vars *vars)
{
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_press, vars);
	mlx_hook(vars->win, DestroyNotify, StructureNotifyMask, close_window, vars);
	mlx_loop_hook(vars->mlx, &game_hook, vars);
	mlx_loop(vars->mlx);
}

/* 
 * Initialises mlx, window and loads background image
 */
void	initialise_game(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		error_handling_vars(ERR_MALLOC, vars);
	vars->win = mlx_new_window(vars->mlx, vars->map->w * TILE_SIZE, (vars->map->h + 1)
			* TILE_SIZE, "Thanks For All The Fish!");
	if (vars->win == NULL)
		error_handling_all(ERR_MALLOC, vars);
	load_background(vars);
}

/*
 * Processes events that are used in the game. Keypresses, all coins collected,
 * win scenario.
 */
int	key_press(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		close_window(vars);
	if (keysym == XK_w)
		move_up(vars);
	if (keysym == XK_a)
		move_left(vars);
	if (keysym == XK_s)
		move_down(vars);
	if (keysym == XK_d)
		move_right(vars);
	if (vars->map->coin_count == 0)
	{
		put_img_to_img(vars->xpm[BG], vars->xpm[CHESTO], (vars->map->exit_x
				* TILE_SIZE) + 8, (vars->map->exit_y * TILE_SIZE) + 8);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0,
			0);
	}
	if (vars->map->coin_count == -1 && vars->map->p_x == vars->map->exit_x
		&& vars->map->p_y == vars->map->exit_y)
	{
		ft_printf("You Win!\n");
		mlx_loop_end(vars->mlx);
	}
	return (0);
}
