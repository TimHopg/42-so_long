/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:57:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/29 17:02:35 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Map is 640 * 480. 20x15 tiles of 32x32 pixels.
 * Optimise by only rendering visible tiles.
 */

# define MAP_WIDTH 20
# define MAP_HEIGHT 15

# define WINDOW_WIDTH MAP_WIDTH * TILE_SIZE // 640
# define WINDOW_HEIGHT MAP_HEIGHT * TILE_SIZE // 480

// typedef struct s_data
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }			t_data;

int	close_window(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	exit(0);
	return (0);
}

void render_background(t_vars *vars, void *sprites[])
{
	int x;
	int y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, sprites[0], x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

// void render_map(void *mlx, void *win, void *tiles[])
// {
//     for (int y = 0; y < MAP_HEIGHT; y++) {
//         for (int x = 0; x < MAP_WIDTH; x++) {
//             int tile_type = map[y][x];
//             mlx_put_image_to_window(mlx, win, tiles[tile_type], x * TILE_SIZE, y * TILE_SIZE);
//         }
//     }
// }

int	key_press(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape) // 65307 == esc linux
		close_window(vars);
	if (keysym == XK_w)
		ft_printf("W\n");
	if (keysym == XK_a)
		ft_printf("A\n");
	if (keysym == XK_s)
		ft_printf("S\n");
	if (keysym == XK_d)
		ft_printf("D\n");
	return (0);
}

// void tile(void *img, t_vars *vars)
// {
// }

/*
 TODO destroy display on linux machines? necessary
 TODO use shell command to edit mlx library file that throws warning during compile
 TODO use keysym instead of keycode (X11/keysym.h)
 TODO silence write value warning on compile of mlx (cc/clang)
 ! MEMORY map, textures, window, (display), mlx
 */

int	main(void)
{
	t_vars	vars;
	char	*relative_path = "./sprites/field.xpm";
	int		img_size;


	// t_data	img;
	img_size = TILE_SIZE;
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (MALLOC_FAIL);
	
	// char *str = "!!!_____the _!__!_!     !_!_ only !_!_!_";
	char *str = " 1 2 3 ";
	// char *set = "!_";
	char *set = " ";
	// printf("%s \n", ft_strpbrk(str, set));
	// str++;
	// ft_printf("%c", *str);
	ft_printf("%d word count\n", count_words(str, set));


	parse_map("maps/basicmap.ber", &vars);
	
	
	
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Thanks For All The Fish!");
	if (vars.win == NULL)
		return (free(vars.mlx), MALLOC_FAIL);
	// img.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// &img.line_length, &img.endian);

	vars.sprites[0] = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_size, &img_size);
	render_background(&vars, vars.sprites);


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
