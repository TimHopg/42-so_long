/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:41:57 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/12 14:02:57 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Each move function turns the player if the path is blocked and moves the
 * the player and prints number of moves to the CL if the path is not.
 */
void	move_up(t_vars *vars)
{
	if (vars->map->map[vars->map->p_y - 1][vars->map->p_x] == '1')
		turn(vars, PB);
	else
		move(vars, PB, 0, -1);
}

void	move_down(t_vars *vars)
{
	if (vars->map->map[vars->map->p_y + 1][vars->map->p_x] == '1')
		turn(vars, PF);
	else
		move(vars, PF, 0, 1);
}

void	move_right(t_vars *vars)
{
	if (vars->map->map[vars->map->p_y][vars->map->p_x + 1] == '1')
		turn(vars, PR);
	else
		move(vars, PR, 1, 0);
}

void	move_left(t_vars *vars)
{
	if (vars->map->map[vars->map->p_y][vars->map->p_x - 1] == '1')
		turn(vars, PL);
	else
		move(vars, PL, -1, 0);
}
