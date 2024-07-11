/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:57:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/11 22:55:58 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Processes events that are used in the game. Keypresses, all coins collected,
 * win scenario.
 */
int	key_press(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		close_window(vars);
	if (keysym == XK_w)
		move_up(vars);
	if (keysym == XK_a)
		move_left(vars);
	if (keysym == XK_s)
		move_down(vars);
	if (keysym == XK_d)
		move_right(vars);
	if (vars->map->coin_count == 0)
	{
		put_img_to_img(vars->xpm[BG], vars->xpm[CHESTO], (vars->map->exit_x
				* TILE_SIZE) + 8, (vars->map->exit_y * TILE_SIZE) + 8);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0,
			0);
		vars->map->coin_count -= 1;
	}
	if (vars->map->coin_count == -1 && vars->map->p_x == vars->map->exit_x
		&& vars->map->p_y == vars->map->exit_y)
	{
		ft_printf("You Win!\n");
		mlx_loop_end(vars->mlx);
	}
	return (0);
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
 * Initialises mlx, window and loads background image
 */
void	initialise_game(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		error_handling_vars(ERR_MALLOC, vars);
	vars->win = mlx_new_window(vars->mlx, vars->map->w * TILE_SIZE, (vars->map->h + 1)
			* TILE_SIZE, "Thanks For All The Fish!");
	if (vars->win == NULL)
		error_handling_all(ERR_MALLOC, vars);
	load_background(vars);
}

// int hook_function(void *param)
// {
    
//     data = (t_data *)param;
//     // Now you can use data->mlx, data->win, etc.
//     // Perform your loop operations here
//     return (0);
// }

/*
 * Initiates the hooks and loops necessary for the game to run.
 */
void	run_game(t_vars *vars)
{
	// mlx_loop_hook(vars->mlx, )
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_press, vars);
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_press, vars);
	mlx_hook(vars->win, DestroyNotify, StructureNotifyMask, close_window, vars);
	mlx_loop(vars->mlx);
}

/*
 ! text that says number of moves and remaining coins
 ! sprite animation chest opening
 ! sprite animation character, idle and moving
 ! enemy + enemy animation
 ! You Win / You Died / Game Over screen
 */

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
	run_game(&vars);
	close_window(&vars);
	return (0);
}
