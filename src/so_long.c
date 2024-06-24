/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:57:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/23 20:10:14 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	void	*exits;
}			t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*text[5];
	t_map	*map;
}			t_vars;

int	close_window(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC) // 65307 == esc linux
		close_window(vars);
	return (0);
}

/*
 TODO destroy display on linux machines? necessary
 TODO use shell command to edit mlx library file that throws warning during compile
 TODO use keysym instead of keycode (X11/keysym.h)
 */

int	main(void)
{
	t_vars	vars;

	// t_data	img;
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (MALLOC_FAIL);
	vars.win = mlx_new_window(vars.mlx, 600, 400, "Thanks For All The Fish!");
	if (vars.win == NULL)
		return (free(vars.mlx), MALLOC_FAIL);
	// img.img = mlx_new_image(vars.mlx, 1920, 1080);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// &img.line_length, &img.endian);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_press, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_window, &vars);
	mlx_loop(vars.mlx);
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
 */
