/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:57:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/12 21:28:07 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

void idle_zombie(t_vars *vars)
{
	
}

int game_hook(void *param)
{
	t_vars *vars;
	vars = (t_vars *)param;
	chest_animation(vars);
	idle_zombie(vars);
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
	// ft_printf("check\n");
	run_game(&vars);
	close_window(&vars);
	return (0);
}

/*
 ! sprite animation chest opening
 ! sprite animation character, idle and moving
 ! enemy + enemy animation
 ! You Win / You Died / Game Over screen
 TODO render bottom line separately so score won't be covered
 TODO render bottom line once at start with MOVES: 0
 TODO only update bottom line when moves updates
 TODO MOVES as graphic and number too. Re-render only number tiles
 ! why so many mallocs on mlx_loop_hook
 TODO map bad if more than one enemy
 */
