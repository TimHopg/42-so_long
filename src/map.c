/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/28 20:47:22 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
0 = empty space
1 = wall
C = collectible
E = map exit
P = player starting position

11111111111111111111
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
11111111111111111111

*/

void is_map_rectangle(t_vars *vars)
{
    int i;
    int map_h;

    map_h = vars->map->h;
    i = 0;
    // ft_printf("map_h %d\n", vars->map->h);
    while (i < map_h)
    {
        // ft_printf("%zu line width\n",ft_strlen(vars->map->map[i]));
        if (ft_strlen(vars->map->map[i]) != (size_t)vars->map->w)
        {
            ft_printf("not rectangle");
            exit(1); // 
        }
        i++;
    }
}

// void check_map_chars(t_vars *vars)
// {
//     while
// }

#include <string.h>

strpbrk();

int is_map_valid(t_vars *vars)
{
    is_map_rectangle(vars);
    // check_map_chars(vars);
    return (1);
}

/*
 * Imports map line by line from ber file into t_vars struct
 * Returns height of map
 */

int import_map(const char *filename, t_vars *vars)
{
    int fd;
    int i;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit(OPEN_FAIL); // free
    line = get_next_line(fd);
    i = 0;
    while (line)
    {
        ft_isinset
        vars->map->map[i] = ft_strtrim(line, "\n");
        if (vars == NULL)
            exit(MALLOC_FAIL); // free
        line = get_next_line(fd);
        i++;
    }
    for (int j = 0; j < i; j++)
        ft_printf("%s\n", vars->map->map[j]);
    return (i);
}

/*
 TODO lines of different length, wrong characters, flood fill fail, more than one
 TODO exit, less than one collectible, no starting position
 */

void parse_map(const char *filename, t_vars *vars)
{
    vars->map->h = import_map(filename, vars);
    if (vars->map->h == 0)
        exit(1); // map fail
    vars->map->w = ft_strlen(vars->map->map[0]);
    // ft_printf("%d map width\n", vars->map->w);
    is_map_valid(vars);
    
    // int width;
    
    // ft_printf("%s\n", vars->map->map[1]);
    // width = ft_strlen(line);
    // vars->map->w = width - 1;
    // vars->win_w = TILE_SIZE * width - 1;
    // ft_printf("%d\n", width - 1);
}

