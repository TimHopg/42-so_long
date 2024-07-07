/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:57:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/07 20:59:17 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Map is 640 * 480. 20x15 tiles of 32x32 pixels.
 * Optimise by only rendering visible tiles.
 */

// # define WINDOW_WIDTH MAP_WIDTH * TILE_SIZE // 640
// # define WINDOW_HEIGHT MAP_HEIGHT * TILE_SIZE // 480

int close_window(t_vars *vars)
{
	free_map(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
	// return (0);
}

int key_press(int keysym, t_vars *vars)
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

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void make_bg(t_img *img, t_vars *vars)
{
	int x;
	int y;

    y = 0;
    while (y < vars->map->h * TILE_SIZE)
    {
        x = 0;
        while (x < vars->map->w * TILE_SIZE)
        {
			my_mlx_pixel_put(img, x, y, 0xFFFF0000);
            x++;
        }
        y++;
    }
}

void initialise_game(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		error_handling_vars(ERR_MALLOC, vars);
	vars->win = mlx_new_window(vars->mlx, vars->map->w * TILE_SIZE, vars->map->h * TILE_SIZE, "Thanks For All The Fish!");
	if (vars->win == NULL)
		error_handling_all(ERR_MALLOC, vars);


	// mlx_clear_window(vars->mlx, vars->win);


	// t_img img;
	// img.img_ptr = mlx_new_image(vars->mlx, vars->map->w * TILE_SIZE, vars->map->h * TILE_SIZE);
	// img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	// make_bg(&img, vars);
	// mlx_put_image_to_window(vars->mlx, vars->win, img.img_ptr, 0, 0);
	
	
	// load_xpm(vars);
	load_background(vars);
}


/*
 TODO destroy display on linux machines? necessary?
 TODO use shell command to edit mlx library file that throws warning during compile
 TODO use keysym instead of keycode (X11/keysym.h)
 TODO silence write value warning on compile of mlx (cc/clang)
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


	// t_img img;
	// img.img = mlx_new_image(vars.mlx, vars.map->w * TILE_SIZE, vars.map->h * TILE_SIZE);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// make_bg(&img, &vars);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	mlx_hook(vars.win, KeyPress, KeyPressMask, key_press, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_window, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_image(vars.mlx, vars.gfx[0]);
	free(vars.gfx[0]);
	close_window(&vars);
	return (0);

	/* 	vars.sprites[0] = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_size, &img_size);
		render_background(&vars, vars.sprites);

		mlx_hook(vars.win, KeyPress, KeyPressMask, key_press, &vars);
		mlx_loop(vars.mlx); */
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
