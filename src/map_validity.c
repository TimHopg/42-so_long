/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:18:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/01 15:20:44 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// /*
//  * Checks 'rectangularity' of map
//  */

// void is_map_rectangle(int map_width, int line_width, t_vars *vars)
// {
//     if (map_width != line_width)
//         error_handling_vars(ERR_RECTANGLE, vars);
// }

/*
 * Parses line checking for bad chars and updating e, p, c count/coords
 */

void parse_line_chars(char *line, t_vars *vars, int h)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!ft_strchr(VALID_CHARS, line[i]))
            error_handling_vars(ERR_CHARS, vars);
        if (line[i] == 'C')
            vars->map->coin_count++;
        if (line[i] == 'P')
        {
            vars->map->p_x = i;
            vars->map->p_y = h;
            vars->map->p_count++;
        }
        if (line[i] == 'E')
        {
            vars->map->exit_x = i;
            vars->map->exit_y = h;
            vars->map->exit_count++;
        }
        ++i;
    }
}

/*
 * Returns true if invalid char encountered !(0,1,E,P,C)
 */

int has_invalid_char(char *str, char *valids)
{
    while (*str)
    {
        if (!ft_strchr(valids, *str))
        {
            return (1);
        }
        str++;
    }
    return (0);
}

void check_map_perimeter(t_vars *vars)
{
    int i;
    int h_max;
    int w_max;

    h_max = vars->map->h - 1;
    w_max = vars->map->w - 1;
    i = -1;
    while (++i <= w_max)
        if (vars->map->map[0][i] != '1' || vars->map->map[h_max][i] != '1')
            error_handling_vars(ERR_MAP_PER, vars);
    i = -1;
    while (++i <= h_max)
        if (vars->map->map[i][0] != '1' || vars->map->map[i][w_max] != '1')
            error_handling_vars(ERR_MAP_PER, vars);
}

/*
 * Checks validity of map.
 */

int is_map_valid(t_vars *vars)
{
    int i;

    i = -1;
    while (++i < vars->map->h)
    {
        // is_map_rectangle(vars->map->w, ft_strlen(vars->map->map[i]), vars);
        if (vars->map->w != (int)ft_strlen(vars->map->map[i]))
            error_handling_vars(ERR_RECTANGLE, vars);
        parse_line_chars(vars->map->map[i], vars, i);
    }
    if (vars->map->p_count != 1)
        error_handling_vars(ERR_PLAYER, vars);
    if (vars->map->exit_count != 1)
        error_handling_vars(ERR_EXIT, vars);
    if (vars->map->coin_count < 1)
        error_handling_vars(ERR_COLL, vars);
    ft_printf("%d width\n", vars->map->w);
    ft_printf("%d height\n", vars->map->h);
    ft_printf("%c char\n", vars->map->map[vars->map->h - 1][1]);
    print_map(vars);
    check_map_perimeter(vars);
    return (1);
}

