/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/04 16:47:11 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void initialise_map(t_vars *vars, char *map_str);

void map_dimensions(t_vars *vars)
{
    int i;

    i = 0;
    while (vars->map->map[i])
        i++;
    vars->map->h = i;
    vars->map->w = ft_strlen(vars->map->map[0]);
}

char *mapfile_to_str(int fd)
{
    char *temp;
    char *line;
    int gnl_status;
    char *map_str;

    map_str = ft_strdup("");
    if (map_str == NULL)
        error_handling_import(ERR_MALLOC, NULL, NULL);
    gnl_status = get_next_line(fd, &line);
    while (gnl_status > 0)
    {
        temp = map_str;
        map_str = ft_strjoin(map_str, line);
        if (map_str == NULL)
            error_handling_import(ERR_MALLOC, temp, line);
        free(temp);
        free(line);
        gnl_status = get_next_line(fd, &line);
    }
    if (gnl_status == GNL_ERROR)
        error_handling_import(ERR_GNL, map_str, NULL);
    return (map_str);
}

/*
 * Function initialises fields of t_map structure
 */

void initialise_map(t_vars *vars, char *map_str)
{
    vars->map = ft_calloc(1, sizeof(t_map));
    // vars->map = malloc(sizeof(t_map));
    if (vars->map == NULL)
        error_handling_import(ERR_MALLOC, map_str, NULL); // !
    // vars->map->w = 0; // can use map{val, val} to initialize values
    // vars->map->h = 0; // can use map{val, val} to initialize values
    // vars->map->coin_count = 0; // can use map{val, val} to initialize values
    // vars->map->p_count = 0; // can use map{val, val} to initialize values
    // vars->map->p_w = 0; // can use map{val, val} to initialize values
    // vars->map->p_h = 0; // can use map{val, val} to initialize values
    // vars->map->exit_count = 0; // can use map{val, val} to initialize values
    // vars->map->exit_w = 0; // can use map{val, val} to initialize values
    // vars->map->exit_h = 0; // can use map{val, val} to initialize values
}

void print_map(t_vars *vars)
{
    int i;

    i = 0;
    while (i < vars->map->h)
        ft_printf("%s\n", (vars->map->map[i++]));
}

void parse_map(int fd, t_vars *vars)
{
    char *map_str;

    map_str = mapfile_to_str(fd);
    initialise_map(vars, map_str);
    vars->map->map = ft_split(map_str, '\n');
    if (vars->map->map == NULL)
        error_handling_import(ERR_MALLOC, map_str, NULL);
    free(map_str);
    if (!vars->map->map[0])
        error_handling_vars(ERR_MAP_H, vars);
    map_dimensions(vars);
    is_map_valid(vars);
    print_map(vars);
    free_map(vars);
}

/*
 TODO if exit coords must be saved, used index in is_map_valid to save them.
 TODO make exit error message + free function, where you pass
    TODO error code so it prints the correct message
 TODO Map errors:
 * non rectangular (lines different length)
 * bad chars
 * flood fill fail
 * less or more than 1 exit
 * less or more than 1 starting position
 * less than one collectible
 * file permissions
 * wall not around perimeter
 * empty map
 * map of new lines
 */
