/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:11:46 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/07 10:39:58 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 ! TEMP Prints vector (map clone)
 */

void print_map_clone (char **map, int height)
{
    ft_printf("\n");
    int i = 0;
    while (i < height)
        ft_printf("%s\n", (map[i++]));
    ft_printf("\n");
}

/*
 * Checks if current position is outside of map boundaries, is a wall or is a
 * position already visited (*) and leaves a breadcrumb of '*'. Then calls 
 * itself for positions above and below, and to the left and right.
 */

void fill(char **map, int p_y, int p_x, t_vars *vars)
{
    if (p_y < 0 || p_y >= vars->map->h || p_x < 0 || p_x >= vars->map->w ||
    map[p_y][p_x] == '1' || map[p_y][p_x] == '*') 
        return;

    if (map[p_y][p_x] == 'C')
        vars->map->coin_count -= 1;
    if (map[p_y][p_x] == 'E')
        vars->map->exit_count -= 1;
    map[p_y][p_x] = '*';
    fill(map, p_y - 1, p_x, vars);
    fill(map, p_y, p_x - 1, vars);
    fill(map, p_y + 1, p_x, vars);
    fill(map, p_y, p_x + 1, vars);
}

/*
 * Sends map to recursive fill function to calculate reachable tiles.
 * Returns 1 (error) if coins not collected or exit not reached.
 */

void flood_fill(t_vars *vars)
{
    char **map_clone;
    int c_count;

    c_count = vars->map->coin_count;
    map_clone = ft_split(vars->map->map_str, '\n');
    if (map_clone == NULL)
        error_handling_vars(ERR_MALLOC, vars);
    fill(map_clone, vars->map->p_y, vars->map->p_x, vars);
    // print_map_clone(map_clone, vars->map->h); // !
    free_vector(map_clone, vars->map->h);
    if (vars->map->coin_count != 0)
        error_handling_vars(ERR_COIN, vars);
    if (vars->map->exit_count != 0)
        error_handling_vars(ERR_EXITU, vars);
    vars->map->coin_count = c_count;
}
