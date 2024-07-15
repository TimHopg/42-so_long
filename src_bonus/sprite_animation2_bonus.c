/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/15 20:41:13 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void random_move(int *moves, int len)
{
    int i;
    int options;

    i = -1;
    options = 0;
    while (++i < len)
        options += moves[i];
    srand(time(0));
    // enemy_move(rand() % options);
}

/*
 * Zombies can only move to empty tiles or where the player is standing.
 * Builds array of possible moves [U,D,L,R].
 */
void moves_possible(t_vars *vars)
{
    int truths[4];
    int len;

    ft_bzero(truths, sizeof(truths));
    if (ft_strchr("0P", vars->map->map[vars->map->b_y - 1][vars->map->b_x]))
        truths[0] = 1;
    if (ft_strchr("0P", vars->map->map[vars->map->b_y + 1][vars->map->b_x]))
        truths[1] = 1;
    if (ft_strchr("0P", vars->map->map[vars->map->b_y][vars->map->b_x - 1]))
        truths[2] = 1;
    if (ft_strchr("0P", vars->map->map[vars->map->b_y][vars->map->b_x + 1]))
        truths[3] = 1;
    len = sizeof(truths) / sizeof(truths[0]);
    random_move(truths, len);
}
