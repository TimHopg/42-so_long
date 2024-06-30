/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:02:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/29 22:24:52 by thopgood         ###   ########.fr       */
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

void error_handling(char *error_code, t_vars *vars)
{
    free_all(vars);
    print_error_msg(error_code);
    exit(1);
}
