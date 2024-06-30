/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/30 14:13:46 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void is_map_rectangle(int map_width, int line_width, t_vars *vars)
{
    if (map_width != line_width)
        error_handling(ERR_RECTANGLE, vars);
}

void parse_line_chars(char *line, t_vars *vars)
{
    while(*line)
    {
        if (!ft_strchr(VALID_CHARS, *line))
            error_handling(ERR_CHARS, vars);
        if (*line == 'C')
            vars->map->coin_count++;
        if (*line == 'P')
            vars->map->p_count++;
        if (*line == 'E')
            vars->map->exit_count++;
        ++line;
    }
}

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
    while (i < vars->map->h)
    {
        is_map_rectangle(vars->map->w, ft_strlen(vars->map->map[i]), vars);
        parse_line_chars(vars->map->map[i], vars);
        i++;
    }
    if (vars->map->p_count != 1)
        error_handling(ERR_PLAYER, vars);
    if (vars->map->exit_count != 1)
        error_handling(ERR_EXIT, vars);
    if (vars->map->coin_count < 1)
        error_handling(ERR_COLL, vars);
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
        error_handling(ERR_OPEN, vars);
    line = get_next_line(fd);
    i = 0;
    while (line)
    {
        ft_printf("%s line\n", line);
        vars->map->map[i] = ft_strtrim(line, "\n");
        if (vars->map->map[i] == NULL)
            error_handling(ERR_MALLOC, vars);
        line = get_next_line(fd);
        i++;
    }
    for (int j = 0; j < i; j++)
        ft_printf("%s\n", vars->map->map[j]);
    return (i);
}

void initialise_map(t_vars *vars)
{
    // vars->map = ft_calloc(1, sizeof(t_map));
    vars->map = malloc(sizeof(t_map));
    vars->map->map = malloc(sizeof(char **));
    if (vars->map == NULL)
        error_handling(ERR_MALLOC, vars);
    vars->map->p_count = 0; // can use map{val, val} to initialize values
    vars->map->exit_count = 0; // can use map{val, val} to initialize values
    vars->map->coin_count = 0; // can use map{val, val} to initialize values
}

/*
 TODO lines of different length, wrong characters, flood fill fail, more than one
 TODO exit, less than one collectible, no starting position
 TODO if exit coords must be saved, used index in is_map_valid to save them.
 TODO make exit error message + free function, where you pass
    TODO error code so it prints the correct message
 TODO file permissions
 TODO wall not around perimeter
 TODO map with too few columns or rows (min 3 of each?)
 */

void parse_map(const char *filename, t_vars *vars)
{
    initialise_map(vars);


    // vars->map->h = import_map(filename, vars);
    // if (vars->map->h == 0)
    //     error_handling(ERR_MAP_H, vars);
    // vars->map->w = ft_strlen(vars->map->map[0]);


    // ft_printf("%d map width\n", vars->map->w);
    is_map_valid(vars);
    
    // int width;
    
    // ft_printf("%s\n", vars->map->map[1]);
    // width = ft_strlen(line);
    // vars->map->w = width - 1;
    // vars->win_w = TILE_SIZE * width - 1;
    // ft_printf("%d\n", width - 1);
}

