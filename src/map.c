/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/01 11:30:49 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void initialise_map(t_vars *vars);

void is_map_rectangle(int map_width, int line_width, t_vars *vars)
{
    if (map_width != line_width)
        error_handling_vars(ERR_RECTANGLE, vars);
}

void parse_line_chars(char *line, t_vars *vars, int h)
{
    int i;

    i = 0;
    while(line[i])
    {
        if (!ft_strchr(VALID_CHARS, line[i]))
            error_handling_vars(ERR_CHARS, vars);
        if (line[i] == 'C')
            vars->map->coin_count++;
        if (line[i] == 'P')
        {            
            vars->map->p_w = i;
            vars->map->p_h = h;
            vars->map->p_count++;
        }
        if (line[i] == 'E')
        {
            vars->map->exit_w = i;
            vars->map->exit_h = h;
            vars->map->exit_count++;
        }
        ++i;
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

void map_dimensions(t_vars *vars)
{
    int i;

    i = 0;
    while (vars->map->map[i])
        i++;
    vars->map->h = i;
    vars->map->w = ft_strlen(vars->map->map[0]);
}

int is_map_valid(t_vars *vars)
{
    int i;

    i = 0;
    while (i < vars->map->h)
    {
        is_map_rectangle(vars->map->w, ft_strlen(vars->map->map[i]), vars);
        parse_line_chars(vars->map->map[i], vars, i);
        i++;
    }
    if (vars->map->p_count != 1)
        error_handling_vars(ERR_PLAYER, vars);
    if (vars->map->exit_count != 1)
        error_handling_vars(ERR_EXIT, vars);
    if (vars->map->coin_count < 1)
        error_handling_vars(ERR_COLL, vars);
    return (1);
}

char *mapfile_to_str(int fd)
{
    char    *temp;
    char    *line;
    int     gnl_status;
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
    return(map_str);
}

/*
 * Function initialises fields of t_map structure
 */

void initialise_map(t_vars *vars)
{
    // vars->map = ft_calloc(1, sizeof(t_map));
    vars->map = malloc(sizeof(t_map));
    // vars->map->map = malloc(sizeof(char *));
    if (vars->map == NULL)
        error_handling_vars(ERR_MALLOC, vars);
    vars->map->p_count = 0; // can use map{val, val} to initialize values
    vars->map->exit_count = 0; // can use map{val, val} to initialize values
    vars->map->coin_count = 0; // can use map{val, val} to initialize values
    vars->map->h = 0; // can use map{val, val} to initialize values
    vars->map->w = 0; // can use map{val, val} to initialize values
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
    initialise_map(vars);
    vars->map->map = ft_split(map_str, '\n');
    if (vars->map->map == NULL)
        error_handling_import(ERR_MALLOC, map_str, NULL);
    free(map_str);
    map_dimensions(vars);
    is_map_valid(vars);
    print_map(vars);
    free_map(vars);




    // vars->map->h = import_map(filename, vars);
    // if (vars->map->h == 0)
    //     error_handling(ERR_MAP_H, vars);
    // vars->map->w = ft_strlen(vars->map->map[0]);


    

    // ft_printf("%d map width\n", vars->map->w);
    // is_map_valid(vars);
    
    // int width;
    
    // ft_printf("%s\n", vars->map->map[1]);
    // width = ft_strlen(line);
    // vars->map->w = width - 1;
    // vars->win_w = TILE_SIZE * width - 1;
    // ft_printf("%d\n", width - 1);
}

/*
 TODO if exit coords must be saved, used index in is_map_valid to save them.
 TODO make exit error message + free function, where you pass
    TODO error code so it prints the correct message
 TODO Map errors:
 * non rectangular (lines different length)
 * bad chars
 ! flood fill fail
 ! less or more than 1 exit
 ! less or more than 1 starting position
 ! less than one collectible
 ! file permissions
 ! wall not around perimeter
 ! map with too few columns or rows (min 3 each?)
 */

// /*
//  * Imports map line by line from ber file into t_vars struct
//  * Returns height of map
//  */

// int import_map(const char *filename, t_vars *vars)
// {
//     int fd;
//     int i;
//     char *line;

//     fd = open(filename, O_RDONLY);
//     if (fd == -1)
//         error_handling_vars(ERR_OPEN, vars);
//     get_next_line(fd, &line);
//     i = 0;
//     while (line)
//     {
//         ft_printf("%s line\n", line);
//         vars->map->map[i] = ft_strtrim(line, "\n");
//         if (vars->map->map[i] == NULL)
//             error_handling_vars(ERR_MALLOC, vars);
//         get_next_line(fd, &line);
//         i++;
//     }
//     for (int j = 0; j < i; j++)
//         ft_printf("%s\n", vars->map->map[j]);
//     return (i);
// }