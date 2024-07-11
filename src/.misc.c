	// mlx_clear_window(vars->mlx, vars->win);


	// t_img img;
	// img.img_ptr = mlx_new_image(vars->mlx, vars->map->w * TILE_SIZE, vars->map->h * TILE_SIZE);
	// img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	// make_bg(&img, vars);
	// mlx_put_image_to_window(vars->mlx, vars->win, img.img_ptr, 0, 0);
	
	
	// load_xpm(vars);

    // void render_map(void *mlx, void *win, void *tiles[])
// {
//     for (int y = 0; y < MAP_HEIGHT; y++) {
//         for (int x = 0; x < MAP_WIDTH; x++) {
//             int tile_type = map[y][x];
//             mlx_put_image_to_window(mlx, win, tiles[tile_type], x * TILE_SIZE, y * TILE_SIZE);
//         }
//     }
// }

// void render_map(t_vars *vars)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < vars->map->h)
//     {
//         x = 0;
//         while (x < vars->map->w)
//         {
//             if (vars->map->map[y][x] == '0')
//                 mlx_put_image_to_window(vars->mlx, vars->win, vars->gfx[FIELD], x * TILE_SIZE, y * TILE_SIZE);
//             if (vars->map->map[y][x] == '1')
//                 mlx_put_image_to_window(vars->mlx, vars->win, vars->gfx[WALL], x * TILE_SIZE, y * TILE_SIZE);
//             x++;
//         }
//         y++;
//     }
// }

// void create_bg(t_vars *vars)
// {
//     int i;

//     i = 0;
//     vars->bg = malloc(vars->map->w * vars->map->h * sizeof(int));
//     if (vars->bg == NULL)
//         exit(0); //
//     while (i < vars->map->w * vars->map->h)
//     {
//         vars->bg[i] = 0xFF0000; // Red background color (ARGB format)
//     }
// }

// void load_xpm(t_vars *vars)
// {
//     int img_size;

//     img_size = TILE_SIZE;
//     // create_bg(vars);
//     // mlx_set_window_bg_img(vars->win, vars->bg, vars->map->w, vars->map->h);
//     // mlx_put_image_to_window(vars->mlx, vars->mlx, vars->bg, vars->map->w, vars->map->h);

//     vars->gfx[1] = mlx_xpm_file_to_image(vars->mlx, "gfx/field.xpm", &img_size, &img_size);
//     vars->gfx[2] = mlx_xpm_file_to_image(vars->mlx, "gfx/wall.xpm", &img_size, &img_size);
//     render_map(vars);
// }

// void load_background(t_vars *vars)
// {
//     t_img base_image;
//     t_img bg;
//     t_img ring;

//     base_image = new_img(vars->map->w * TILE_SIZE, vars->map->h * TILE_SIZE, vars);
//     {
//         bg = new_file_img("gfx/field.xpm", vars);
//         if (!bg.img_ptr)
//             exit(2); // !
//         put_img_to_img(base_image, bg, 0, 0);
//     }
//     {
//         ring = new_file_img("gfx/wall.xpm", vars);
//         if (!ring.img_ptr)
//             exit(2); // !
//         put_img_to_img(base_image, ring, 0, 0);
//     }
//     mlx_put_image_to_window(vars->mlx, vars->win, base_image.img_ptr, 0, 0);
// }


	// t_img img;
	// img.img = mlx_new_image(vars.mlx, vars.map->w * TILE_SIZE, vars.map->h * TILE_SIZE);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// make_bg(&img, &vars);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	/* 	vars.sprites[0] = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_size, &img_size);
		render_background(&vars, vars.sprites);

		mlx_hook(vars.win, KeyPress, KeyPressMask, key_press, &vars);
		mlx_loop(vars.mlx); */

		// void my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
// 	char *dst;

// 	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 	*(unsigned int *)dst = color;
// }

// void make_bg(t_img *img, t_vars *vars)
// {
// 	int x;
// 	int y;

//     y = 0;
//     while (y < vars->map->h * TILE_SIZE)
//     {
//         x = 0;
//         while (x < vars->map->w * TILE_SIZE)
//         {
// 			my_mlx_pixel_put(img, x, y, 0xFFFF0000);
//             x++;
//         }
//         y++;
//     }
// }

	// mlx_loop_hook(vars->mlx, hook_main, vars);

	// void hook_main(void *param)
// {
// 	t_vars *vars;

// 	vars = (t_vars *)param;
// 	vars->frame++;
// 	if (vars->frame % 5)
// 		return ;
	
// }