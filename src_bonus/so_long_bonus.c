/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:57:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/16 12:49:41 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Checks if enemy and player occupy same position on map and quits game
 */
void lose_check(t_vars *vars)
{
    if (vars->b.x == vars->map->p_x && vars->b.y == vars->map->p_y)
    {
        ft_printf("GAME OVER\nYou Lose!\n");
        close_window(vars);
    }
}

/*
 * Parses fd if arguments are 1 and of .ber file extension.
 */
int	parse_fd(int ac, char **av)
{
	int	fd;
	int	ber_len;

	ber_len = ft_strlen(".ber");
	if (ac == 1)
		error_handling_import(ERR_NOMAP, NULL, NULL);
	else if (ac > 2)
		error_handling_import(ERR_ARGS, NULL, NULL);
	else if (ft_strncmp(av[1] + ft_strlen(av[1]) - ber_len, ".ber",
			ber_len) != 0)
		error_handling_import(ERR_FILETYPE, NULL, NULL);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_handling_import(ERR_OPEN, NULL, NULL);
	return (fd);
}

/*
 * Function hooks into game loop that runs every frame of the game.
 */
int game_hook(void *param)
{
	t_vars *vars;
	vars = (t_vars *)param;
	chest_animation(vars);
	idle_zombie(vars);
	lose_check(vars);
	vars->loop++;
    return (0);
}

/*
 * Runs game. Loads variables structure and initialises to zero. Parses map
 * Run's game and then closes elegantly.
 */
int	main(int ac, char **av)
{
	int		fd;
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	fd = parse_fd(ac, av);
	parse_map(fd, &vars);
	initialise_game(&vars);
	moves_possible(&vars);
	run_game(&vars);
	close_window(&vars);
	return (0);
}

/*
 * mlx_loop_hook mallocs and frees on every frame resulting in a large
	* number of mallocs and frees
 TODO You Win / You Died / Game Over screen
 TODO MOVES as graphic and number too. Re-render only number tiles
 * game state variable that updates when game is over. Can stop animations
	* and counters once game is over
 */
