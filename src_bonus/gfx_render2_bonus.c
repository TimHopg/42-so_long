/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_render2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:41:36 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/12 13:33:21 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void render_text(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, 10, (vars->map->h + 1) * TILE_SIZE - TEXT_H, TEXT_COLOR, "Moves:");
}
