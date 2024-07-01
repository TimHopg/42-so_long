/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:02:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/01 12:21:37 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void print_error_msg(char *error_code)
{
    ft_printf(error_code);
}

void free_all(t_vars *vars)
{
    int i;

    i = 0;
    while (i < vars->map->h)
    {
        if (vars->map->map[i])
            free(vars->map->map[i]);
        i++;
    }
}

void free_map(t_vars *vars)
{
    int i;

    i = 0;
    while (i < vars->map->h)
        free(vars->map->map[i++]);
    free(vars->map->map);
    free(vars->map);
}

void error_handling_vars(char *error_code, t_vars *vars)
{
    free_map(vars);
    // free_all(vars);
    print_error_msg(error_code);
    exit(1);
}

void error_handling_import(char *error_code, char *str1, char *str2)
{
    if (str1)
        free(str1);
    if (str2)
        free(str2);
    print_error_msg(error_code);
    exit(1);
}
