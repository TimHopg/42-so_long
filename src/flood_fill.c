/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:11:46 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/04 17:12:07 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void clone_map(t_vars *vars)
{
    char **map_copy;
    int i;

    char **map_copy = malloc((vars->map->h + 1) * sizeof(char *));
    if (map_copy == NULL)
        exit(0);
    i = 0;
    while (i < vars->map->h)
    {
        map_copy[i] = malloc((strlen(original[i]) + 1) * sizeof(char));

        i++;
    }
    for (int i = 0; i < num_strings; i++) {
    strcpy(copy[i], original[i]);
}
copy[num_strings] = NULL; // terminate the copy array with a NULL pointer
}

/*
 * Checks if current position is outside of map boundaries, is a wall or is a
 * position already visited (*) and leaves a breadcrumb of '*'. Then calls 
 * itself for positions above and below, and to the left and right.
 */

void fill(t_map *map, int p_y, int p_x)
{
    if (p_y < 0 || p_y >= map->h || p_x < 0 || p_x >= map->w ||
    map->map[p_y][p_x] == '1' || map->map[p_y][p_x] == '*') 
        return;

    if (map->map[p_y][p_x] == 'C')
        map->coin_count -= 1;
    if (map->map[p_y][p_x] == 'E')
        map->exit_count -= 1;
    map->map[p_y][p_x] = '*';
    fill(map, p_y - 1, p_x);
    fill(map, p_y, p_x - 1);
    fill(map, p_y + 1, p_x);
    fill(map, p_y, p_x + 1);
}

/*
 * Sends map to recursive fill function to calculate reachable tiles.
 * Returns 1 (error) if coins not collected or exit not reached.
 */

void flood_fill(t_vars *vars)
{
    t_map *fmap;
    fmap = vars->map;

    fill(fmap, fmap->p_y, fmap->p_x);
    
    ft_printf("\n");
    int i = 0;
    while (i < fmap->h)
        ft_printf("%s\n", (fmap->map[i++]));
    ft_printf("\n");

    if (fmap->coin_count != 0)
        error_handling_vars(ERR_COIN, vars);
    if (fmap->exit_count != 0)
        error_handling_vars(ERR_EXITU, vars);
}
