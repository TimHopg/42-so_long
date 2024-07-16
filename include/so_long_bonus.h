/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:22 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/16 16:04:38 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/include/libft.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include "mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define TSZ 32
# define FSZ 10
# define VALID_CHARS "01CEPB"
# define TEXT_H 11
# define TEXT_COLOR 0x00022930

// Error strings
# define ERR_MALLOC "Malloc error\n"
# define ERR_NOMAP "No map file given\n"
# define ERR_ARGS "Too many arguments given\n"
# define ERR_FILETYPE "Map file type must be .ber\n"
# define ERR_OPEN "Error opening map file\n"
# define ERR_RECTANGLE "Map not rectangular\n"
# define ERR_CHARS "Bad chars in map file\n"
# define ERR_PLAYER "Wrong number of player starting positions\n"
# define ERR_EXIT "Wrong number of exits\n"
# define ERR_COLL "No collectibles\n"
# define ERR_MAP_H "No map content\n"
# define ERR_MAP_PER "Map not enclosed by walls\n"
# define ERR_GNL "Get next line error\n"
# define ERR_COIN "Some coins unreachable\n"
# define ERR_EXITU "Exit unreachable\n"
# define ERR_ENEMY "Too many/no enemies\n"

// Moves
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3
# define NO_MOVE 4

// Image macros
# define XPM_MAX 23
# define BG 0
# define XTRA_LINE 11
# define FIELD 1
# define WALL 2
# define COIN 3
# define PF 4
# define PB 7
# define PL 8
# define PR 9
# define CHESTC 5
# define CHESTO 6
# define TATA 10
# define SP1 12
# define SP2 13
# define SP3 14
# define SP4 15
# define BAD_I1 16
# define BAD_I2 17
# define BAD_I3 18
# define BAD_I4 19
# define BAD_I5 20
# define BAD_L 21
# define BAD_R 22
// Fonts
# define FONT_MAX 11
# define MOVES 10
# define ZERO 0
# define ONE 1
# define TWO 2
# define THREE 3
# define FOUR 4
# define FIVE 5
# define SIX 6
# define SEVEN 7
# define EIGHT 8
# define NINE 9

# define ZOM_SPEED 40000

typedef struct s_tab
{
	int x;
	int y;
} t_tab;

typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	int				h;
	int				w;
	int				bpp;
	int				endian;
	int				line_len;
}					t_img;

typedef struct s_map
{
	char			**map;
	char			*map_str;
	int				exit_x;
	int				exit_y;
	int				exit_count;
	int				coin_count;
	int				p_count;
	int				p_x;
	int				p_y;
	int				b_x;
	int				b_y;
	int				w;
	int				h;
}					t_map;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_tab			b;
	int				win_w;
	int				win_h;
	int				moves;
	t_img			xpm[XPM_MAX];
	t_img			font[FONT_MAX];
	t_map			*map;
	unsigned long	frames;
	int				chest_event;
	int				slash;
	unsigned long	loop;
}					t_vars;

// Free & error
void				free_map(t_vars *vars);
void				free_vector(char **vect, int len);
void				free_gfx(t_vars *vars);
int					close_window(t_vars *vars);
void				error_handling_vars(char *error_code, t_vars *vars);
void				error_handling_import(char *error_code, char *str1,
						char *str2);
void				error_handling_all(char *error_code, t_vars *vars);
// Map Parsing
int					is_map_valid(t_vars *vars);
void				flood_fill(t_vars *vars);
void				parse_map(int fd, t_vars *vars);
// Gfx
void				load_xpm(t_vars *vars);
void				img_to_img(t_img dst, t_img src, int x, int y);
void				put_pixel_img(t_img img, int x, int y, int color);
void				load_background(t_vars *vars);
void				load_gfx_font(t_vars *vars);
void				render_map(t_vars *vars);
unsigned int		get_pixel_img(t_img img, int x, int y);
void				extra_line(t_vars *vars);
// void				render_text(t_vars *vars);
void				render_enemies(t_vars *vars);
t_img				new_file_img(char *path, t_vars *vars);
void				moves_to_img(t_vars *vars);
// Movement
void				turn(t_vars *vars, int img);
void				move(t_vars *vars, int img, int x, int y);
void				move_up(t_vars *vars);
void				move_down(t_vars *vars);
void				move_right(t_vars *vars);
void				move_left(t_vars *vars);
// Animation
void				print_moves(t_vars *vars);
void				chest_animation(t_vars *vars);
void				idle_zombie(t_vars *vars);
void				moves_possible(t_vars *vars);
// Main
void				run_game(t_vars *vars);
void				initialise_game(t_vars *vars);
int					key_press(int keysym, t_vars *vars);
int					game_hook(void *param);
int					main(int ac, char **av);

/*
 * 0 = empty space
 * 1 = wall
 * C = collectible
 * E = map exit
 * P = player starting position
 * B = bad guy starting position
 */

#endif