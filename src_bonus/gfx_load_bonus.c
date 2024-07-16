/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_load_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:50:37 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/16 21:21:32 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Creates image for background.
 */
t_img	new_img(int w, int h, t_vars *vars)
{
	t_img	image;

	image.img_ptr = mlx_new_image(vars->mlx, w, h);
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}

/*
 * Creates image struct from file then copies pixel data from that struct
 */
t_img	new_file_img(char *path, t_vars *vars)
{
	t_img	image;

	image.img_ptr = mlx_xpm_file_to_image(vars->mlx, path, &image.w, &image.h);
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	return (image);
}

/*
 * Loads background 'BG' image of window size. Loads each XPM file into struct.
 */
void	load_gfx(t_vars *vars)
{
	vars->xpm[BG] = new_img(vars->map->w * TSZ, (vars->map->h) * TSZ, vars);
	vars->xpm[XTRA_LINE] = new_img(vars->map->w * TSZ, TSZ, vars);
	vars->xpm[FIELD] = new_file_img("gfx/field.xpm", vars);
	vars->xpm[WALL] = new_file_img("gfx/wall.xpm", vars);
	vars->xpm[COIN] = new_file_img("gfx/coin.xpm", vars);
	vars->xpm[PF] = new_file_img("gfx/pf.xpm", vars);
	vars->xpm[PB] = new_file_img("gfx/pb.xpm", vars);
	vars->xpm[PL] = new_file_img("gfx/pl.xpm", vars);
	vars->xpm[PR] = new_file_img("gfx/pr.xpm", vars);
	vars->xpm[CHESTC] = new_file_img("gfx/chestc.xpm", vars);
	vars->xpm[CHESTO] = new_file_img("gfx/chesto.xpm", vars);
	vars->xpm[TATA] = new_file_img("gfx/tatami.xpm", vars);
	vars->xpm[SP1] = new_file_img("gfx/spark1.xpm", vars);
	vars->xpm[SP2] = new_file_img("gfx/spark2.xpm", vars);
	vars->xpm[SP3] = new_file_img("gfx/spark3.xpm", vars);
	vars->xpm[SP4] = new_file_img("gfx/spark4.xpm", vars);
	vars->xpm[LOSE] = new_file_img("gfx/lose.xpm", vars);
	vars->xpm[WIN] = new_file_img("gfx/win.xpm", vars);
}

/*
 * Loads enemy graphics files.
 * Checks for malloc errors on all images and handles appropriately.
 */
void	load_gfx_enemy(t_vars *vars)
{
	int	x;

	vars->xpm[BAD_I1] = new_file_img("gfx/bad_i1.xpm", vars);
	vars->xpm[BAD_I2] = new_file_img("gfx/bad_i2.xpm", vars);
	vars->xpm[BAD_I3] = new_file_img("gfx/bad_i3.xpm", vars);
	vars->xpm[BAD_I4] = new_file_img("gfx/bad_i4.xpm", vars);
	vars->xpm[BAD_I5] = new_file_img("gfx/bad_i5.xpm", vars);
	vars->xpm[BAD_L] = new_file_img("gfx/bad_l.xpm", vars);
	vars->xpm[BAD_R] = new_file_img("gfx/bad_r.xpm", vars);
	x = -1;
	while (++x < XPM_MAX)
		if (!(vars->xpm[x].img_ptr))
			error_handling_all(ERR_MALLOC, vars);
}

/*
 * Loads gfx, renders map and prints image to window
 */
void	load_background(t_vars *vars)
{
	load_gfx(vars);
	load_gfx_font(vars);
	load_gfx_enemy(vars);
	render_map(vars);
	render_enemies(vars);
	extra_line(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm[BG].img_ptr, 0, 0);
	print_moves(vars);
}
