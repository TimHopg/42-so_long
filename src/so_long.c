/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:57:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/08 20:17:29 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Map is 640 * 480. 20x15 tiles of 32x32 pixels.
 * Optimise by only rendering visible tiles.
 */



int key_press(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape) // 65307 == esc linux
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
		put_img_to_img(vars->xpm[BG], vars->xpm[CHESTO], (vars->map->exit_x * TILE_SIZE) + 8, (vars->map->exit_y * TILE_SIZE) + 8);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
		vars->map->coin_count -= 1;
	}
	if (vars->map->coin_count == -1
		&& vars->map->p_x == vars->map->exit_x
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
int parse_fd(int ac, char **av)
{
	int fd;
	int ber_len;

	ber_len = ft_strlen(".ber");
	if (ac == 1)
		error_handling_import(ERR_NOMAP, NULL, NULL);
	else if (ac > 2)
		error_handling_import(ERR_ARGS, NULL, NULL);
	else if (ft_strncmp(av[1] + ft_strlen(av[1]) - ber_len, ".ber", ber_len) != 0)
		error_handling_import(ERR_FILETYPE, NULL, NULL);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_handling_import(ERR_OPEN, NULL, NULL);
	return (fd);
}

void initialise_game(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		error_handling_vars(ERR_MALLOC, vars);
	vars->win = mlx_new_window(vars->mlx, vars->map->w * TILE_SIZE, vars->map->h * TILE_SIZE, "Thanks For All The Fish!");
	if (vars->win == NULL)
		error_handling_all(ERR_MALLOC, vars);
	load_background(vars);
	// vars->moves = 1;
}

void run_game(t_vars *vars)
{
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_press, vars);
	mlx_hook(vars->win, DestroyNotify, StructureNotifyMask, close_window, vars);
	mlx_loop(vars->mlx);
}

/*
 TODO destroy display on linux machines? necessary?
 TODO use shell command to edit mlx library file that throws warning during compile
 TODO use keysym instead of keycode (X11/keysym.h)
 TODO silence write value warning on compile of mlx (cc/clang)
 TODO if graphics file is missing. handle!
 ! MEMORY map, textures, window, (display), mlx
 */

int main(int ac, char **av)
{
	int fd;
	t_vars vars;

	ft_bzero(&vars, sizeof(t_vars));
	fd = parse_fd(ac, av);
	parse_map(fd, &vars);
	initialise_game(&vars);
	run_game(&vars);
	close_window(&vars);
	return (0);
}

/*
 * if (all_collectables_collected && exit_count == 1)
 *	return (map_valid);
 * if (on_wall)
 *	return (map_invalid);
 * if (on_collectable)
 *	collectables++;
 * if (on_exit)
 *	exits++;
 * replace_current_position_with_wall;
 * if (one_of_the_four_adjacent_directions_is_possible)
 *	return (map_valid);
 * return (map_invalid);
 TODO change error management to have access to free map, vars, all etc.
	TODO create free.c file with all frees and errors stay in error.c
 * destroy_display is to clear mlx init on certain mlx versions
 */
