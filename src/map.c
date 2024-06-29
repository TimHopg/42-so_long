/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/29 19:14:28 by thopgood         ###   ########.fr       */
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

void is_map_rectangle(int map_width, int line_width)
{
    if (map_width != line_width)
        {
            ft_printf("Map not rectangle");
            exit(1); // 
        }
}

void parse_line_chars(char *line, t_vars *vars)
{
    while(*line)
    {
        if (!ft_strchr(VALID_CHARS, *line))
        {
            ft_printf("Bad chars in map file\n");
            exit(OPEN_FAIL); // wrong chars, free
        }
        if (*line == 'C')
            vars->map->coin_count++;
        if (*line == 'P')
            vars->map->p_count++;
        if (*line == 'E')
            vars->map->exit_count++;
        ++line;
    }
}

// #include <string.h>

// strpbrk();

int has_invalid_char(char *str, char *valids)
{
    while(*str)
    {
        if (!ft_strchr(valids, *str))
        {
            return (1);
        }
        str++;
    }
    return (0);
}

int is_map_valid(t_vars *vars)
{
    int i;

    i = 0;
    vars->map->p_count = 0; // can use map{val, val} to initialize values
    vars->map->exit_count = 0; // can use map{val, val} to initialize values
    vars->map->coin_count = 0; // can use map{val, val} to initialize values
    while (i < vars->map->h)
    {
        is_map_rectangle(vars->map->w, ft_strlen(vars->map->map[i]));
        parse_line_chars(vars->map->map[i], vars);
        i++;
    }
    if (vars->map->p_count != 1)
    {
        ft_printf("There are %d player positions.\n", vars->map->p_count);
        exit(1); // free
    }
    if (vars->map->exit_count != 1)
    {
        ft_printf("There are %d exits.\n", vars->map->exit_count);
        exit(1); // free
    }
    if (vars->map->coin_count < 1)
    {
        ft_printf("There are %d collectibles.\n", vars->map->coin_count);
        exit(1); // free
    }


    // is_map_rectangle(vars);
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
    {
        ft_printf("Map file opening error\n");
        exit(OPEN_FAIL); // free
    }
    line = get_next_line(fd);
    i = 0;
    while (line)
    {
        vars->map->map[i] = ft_strtrim(line, "\n");
        if (vars->map->map[i] == NULL)
        {
            ft_printf("Malloc error: Map assigning\n");
            exit(MALLOC_FAIL); // free
        }
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
 TODO if exit coords must be saved, used index in is_map_valid to save them.
 TODO make exit error message + free function, where you pass
    TODO error code so it prints the correct message
 */

void parse_map(const char *filename, t_vars *vars)
{
    vars->map->h = import_map(filename, vars);
    if (vars->map->h == 0)
    {
        ft_printf("Map height of zero\n");
        exit(1); // map fail
    }
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

