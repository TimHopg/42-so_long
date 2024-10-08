/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:02:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/09/17 15:50:16 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Prints "Error" followed by custom error message
 */
void	print_error_msg(char *error_code)
{
	ft_printf("Error\n");
	ft_printf(error_code);
}

/*
 * Handles freeing heap memory after map has been parsed
 */
void	error_handling_vars(char *error_code, t_vars *vars)
{
	free_map(vars);
	print_error_msg(error_code);
	exit(1);
}

/*
 * Handles freeing memory during map parsing phase
 */
void	error_handling_import(char *error_code, char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	print_error_msg(error_code);
	exit(1);
}

/*
 * Frees all
 */
void	error_handling_all(char *error_code, t_vars *vars)
{
	free_map(vars);
	free_gfx(vars);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	print_error_msg(error_code);
	exit(1);
}

/*
 * Frees all without processing error
 */
int	close_window(t_vars *vars)
{
	free_map(vars);
	free_gfx(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}
