/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/16 21:27:57 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Updates map co-ordinates where player/enemy has been.
 */
void	update_coords(t_vars *vars, t_tab *tab, t_tab moves)
{
	if (vars->map->map[tab->y][tab->x] == 'E')
		vars->map->map[tab->y][tab->x] = 'E';
	else
		vars->map->map[tab->y][tab->x] = '0';
	tab->x += moves.x;
	tab->y += moves.y;
}

/*
 * Moves enemy and updates image.
 */
void	enemy_move(t_vars *vars, int img, t_tab moves, t_tab *tab)
{
	img_to_img(vars->xpm[BG], vars->xpm[FIELD], tab->x * TSZ, tab->y * TSZ);
	img_to_img(vars->xpm[BG], vars->xpm[img], ((tab->x + moves.x) * TSZ),
		((tab->y + moves.y) * TSZ));
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
	update_coords(vars, tab, moves);
}

/*
 * sends the appropriate move coordinates to the enemy_move function.
 */
void	move_select(t_vars *vars, t_tab *tab, int dir)
{
	t_tab	moves;

	if (dir == UP)
	{
		moves = (t_tab){0, -1};
		return (enemy_move(vars, BAD_L, moves, tab));
	}
	else if (dir == DOWN)
	{
		moves = (t_tab){0, 1};
		return (enemy_move(vars, BAD_R, moves, tab));
	}
	else if (dir == LEFT)
	{
		moves = (t_tab){-1, 0};
		return (enemy_move(vars, BAD_L, moves, tab));
	}
	else if (dir == RIGHT)
	{
		moves = (t_tab){1, 0};
		return (enemy_move(vars, BAD_R, moves, tab));
	}
	moves = (t_tab){0, 0};
	enemy_move(vars, BAD_R, moves, tab);
}

/*
 * Determines how many possible moves are available to the enemy, if none,
 * attack animation takes place and no movement. Else, a random one of the
 * possible moves is chosen using rand() and time(0) as the seed so each
 * game is unique.
 */
void	random_move(t_vars *vars, int *moves, int len)
{
	int	i;
	int	options;
	int	choice_index;

	i = -1;
	options = 0;
	while (++i < len)
		options += moves[i];
	if (options == 0)
		return (move_select(vars, &(vars->b), NO_MOVE));
	srand(time(0));
	i = -1;
	choice_index = rand() % options;
	while (++i < len)
	{
		if (moves[i])
		{
			if (choice_index == 0)
				return (move_select(vars, &(vars->b), i));
			choice_index -= 1;
		}
	}
}

/*
 * Zombies can only move to empty tiles or where the player is standing.
 * Builds array of possible moves [U,D,L,R].
 */
void	moves_possible(t_vars *vars)
{
	int	truths[4];
	int	len;

	ft_bzero(truths, sizeof(truths));
	if (ft_strchr("0P", vars->map->map[vars->b.y - 1][vars->b.x]))
		truths[0] = 1;
	if (ft_strchr("0P", vars->map->map[vars->b.y + 1][vars->b.x]))
		truths[1] = 1;
	if (ft_strchr("0P", vars->map->map[vars->b.y][vars->b.x - 1]))
		truths[2] = 1;
	if (ft_strchr("0P", vars->map->map[vars->b.y][vars->b.x + 1]))
		truths[3] = 1;
	len = sizeof(truths) / sizeof(truths[0]);
	random_move(vars, truths, len);
}
