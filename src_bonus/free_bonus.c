/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:23:34 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/16 16:41:37 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Frees all strings in vector then frees vector itself
 */
void	free_vector(char **vect, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(vect[i++]);
	free(vect);
}

/*
 * frees fields of map struct
 */
void	free_map(t_vars *vars)
{
	free(vars->map->map_str);
	free_vector(vars->map->map, vars->map->h);
	free(vars->map);
}

/*
 * Frees each image file
 */
void	free_gfx(t_vars *vars)
{
	int	x;

	x = -1;
	while (++x < XPM_MAX)
		if (vars->xpm[x].img_ptr)
			mlx_destroy_image(vars->mlx, vars->xpm[x].img_ptr);
	x = -1;
	while (++x < FONT_MAX)
		if (vars->font[x].img_ptr)
			mlx_destroy_image(vars->mlx, vars->font[x].img_ptr);
}
