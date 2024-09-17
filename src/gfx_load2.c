/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_load2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:50:37 by thopgood          #+#    #+#             */
/*   Updated: 2024/09/17 15:50:46 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Loads font images into struct.
 */
void	load_gfx_font(t_vars *vars)
{
	int	x;

	vars->font[MOVES] = new_file_img("gfx/moves.xpm", vars);
	vars->font[ZERO] = new_file_img("gfx/zero.xpm", vars);
	vars->font[ONE] = new_file_img("gfx/one.xpm", vars);
	vars->font[TWO] = new_file_img("gfx/two.xpm", vars);
	vars->font[THREE] = new_file_img("gfx/three.xpm", vars);
	vars->font[FOUR] = new_file_img("gfx/four.xpm", vars);
	vars->font[FIVE] = new_file_img("gfx/five.xpm", vars);
	vars->font[SIX] = new_file_img("gfx/six.xpm", vars);
	vars->font[SEVEN] = new_file_img("gfx/seven.xpm", vars);
	vars->font[EIGHT] = new_file_img("gfx/eight.xpm", vars);
	vars->font[NINE] = new_file_img("gfx/nine.xpm", vars);
	x = -1;
	while (++x < FONT_MAX)
		if (!(vars->font[x].img_ptr))
			error_handling_all(ERR_MALLOC, vars);
}
