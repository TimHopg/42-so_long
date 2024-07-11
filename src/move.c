/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:41:57 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/11 10:17:59 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move(t_vars *vars, int img, int x, int y)
{
    put_img_to_img(vars->xpm[BG], vars->xpm[img], ((vars->map->p_x + x) * TILE_SIZE) + 8, ((vars->map->p_y + y) * TILE_SIZE) + 8);
    put_img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->p_x * TILE_SIZE, vars->map->p_y * TILE_SIZE);
    if (vars->map->p_x == vars->map->exit_x && vars->map->p_y == vars->map->exit_y)
        put_img_to_img(vars->xpm[BG], vars->xpm[CHESTC], (vars->map->p_x * TILE_SIZE) + 8, (vars->map->p_y * TILE_SIZE) + 8);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
    if (vars->map->map[vars->map->p_y + y][vars->map->p_x + x] == 'C')
    {
        vars->map->coin_count -= 1;
        vars->map->map[vars->map->p_y + y][vars->map->p_x + x] = '0';
    }
    vars->map->p_x += x;
    vars->map->p_y += y;
}

void turn(t_vars *vars, int img)
{
    if (vars->map->map[vars->map->p_y][vars->map->p_x] == 'E')
        put_img_to_img(vars->xpm[BG], vars->xpm[CHESTC], vars->map->p_x * TILE_SIZE + 8, vars->map->p_y * TILE_SIZE + 8);
    else
        put_img_to_img(vars->xpm[BG], vars->xpm[FIELD], vars->map->p_x * TILE_SIZE, vars->map->p_y * TILE_SIZE);
    put_img_to_img(vars->xpm[BG], vars->xpm[img], ((vars->map->p_x) * TILE_SIZE) + 8, ((vars->map->p_y) * TILE_SIZE) + 8);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
}

void move_up(t_vars *vars)
{
    if (vars->map->map[vars->map->p_y - 1][vars->map->p_x] == '1')
        turn(vars, PB);
    else
    {
        ft_printf("Moves: %d\n", ++(vars->moves));
        move(vars, PB, 0, -1);
    }
}

void move_down(t_vars *vars)
{
    if (vars->map->map[vars->map->p_y + 1][vars->map->p_x] == '1')
        turn(vars, PF);
    else
    {
        ft_printf("Moves: %d\n", ++(vars->moves));
        move(vars, PF, 0, 1);
    }
}

void move_right(t_vars *vars)
{
    if (vars->map->map[vars->map->p_y][vars->map->p_x + 1] == '1')
        turn(vars, PR);
    else
    {
        ft_printf("Moves: %d\n", ++(vars->moves));
        move(vars, PR, 1, 0);
    }
}

void move_left(t_vars *vars)
{
    if (vars->map->map[vars->map->p_y][vars->map->p_x - 1] == '1')
        turn(vars, PL);
    else
    {
        ft_printf("Moves: %d\n", ++(vars->moves));
        move(vars, PL, -1, 0);
    }
}
