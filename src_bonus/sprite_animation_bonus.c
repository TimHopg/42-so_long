/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/12 17:58:08 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void exit_to_window(t_vars *vars, int dst, int src)
{
	put_img_to_img(vars->xpm[dst], vars->xpm[FIELD], vars->map->exit_x * TILE_SIZE, vars->map->exit_y * TILE_SIZE);
	put_img_to_img(vars->xpm[dst], vars->xpm[CHESTO], vars->map->exit_x * TILE_SIZE + 8, vars->map->exit_y * TILE_SIZE + 8);
	put_img_to_img(vars->xpm[dst], vars->xpm[src], vars->map->exit_x * TILE_SIZE, vars->map->exit_y * TILE_SIZE);
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
		put_img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->exit_x * TILE_SIZE, vars->map->exit_y * TILE_SIZE);
		put_img_to_img(vars->xpm[BG], vars->xpm[CHESTO], vars->map->exit_x * TILE_SIZE + 8, vars->map->exit_y * TILE_SIZE + 8);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
	}
}

void print_moves(t_vars *vars)
{
	char *moves_str;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[XTRA_LINE].img_ptr, 0, vars->map->h * TILE_SIZE);
	mlx_string_put(vars->mlx, vars->win, 10, (vars->map->h + 1) * TILE_SIZE - TEXT_H, TEXT_COLOR, "Moves:");
	moves_str = ft_itoa(vars->moves);
	if (moves_str == NULL)
		error_handling_all(ERR_MALLOC, vars);
	mlx_string_put(vars->mlx, vars->win, 50, (vars->map->h + 1) * TILE_SIZE - TEXT_H, TEXT_COLOR, moves_str);
	free(moves_str);
}
