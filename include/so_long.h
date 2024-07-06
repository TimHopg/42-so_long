/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:22 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/06 15:52:42 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "../libft/include/libft.h"
#include "X11/X.h"
#include "X11/keysym.h"
#include "mlx.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define TILE_SIZE 32
#define VALID_CHARS "01CEP"

// Errors
#define ERR_MALLOC "Malloc error\n"
#define ERR_OPEN "Error opening map file\n"
#define ERR_RECTANGLE "Map not rectangular\n"
#define ERR_CHARS "Bad chars in map file\n"
#define ERR_PLAYER "Wrong number of player starting positions\n"
#define ERR_EXIT "Wrong number of exits\n"
#define ERR_COLL "No collectibles\n"
#define ERR_MAP_H "No map content\n"
#define ERR_MAP_PER "Map not enclosed by walls\n"
#define ERR_GNL "Get next line error\n"
#define ERR_COIN "Some coins unreachable\n"
#define ERR_EXITU "Exit unreachable\n"

typedef struct s_map
{
	char **map;
	char *map_str;
	int exit_x;
	int exit_y;
	int exit_count;
	int coin_count;
	int p_count;
	int p_x;
	int p_y;
	int w;
	int h;
} t_map;

typedef struct s_vars
{
	void *mlx;
	void *win;
	int win_w;
	int win_h;
	void *sprites[5];
	t_map *map;
} t_vars;

void free_map(t_vars *vars);
void free_vector(char **vect, int len);
void error_handling_vars(char *error_code, t_vars *vars);
void error_handling_import(char *error_code, char *str1, char *str2);
int is_map_valid(t_vars *vars);
void flood_fill(t_vars *vars);
void parse_map(int fd, t_vars *vars);
void print_map(t_vars *vars);
int main(int ac, char **av);

// Events
// enum
// {
// 	ON_KEYDOWN = 2,
// 	ON_KEYUP = 3,
// 	ON_MOUSEDOWN = 4,
// 	ON_MOUSEUP = 5,
// 	ON_MOUSEMOVE = 6,
// 	ON_EXPOSE = 12,
// 	ON_DESTROY = 17
// };

/*
0 = empty space
1 = wall
C = collectible
E = map exit
P = player starting position

11111111111111111111
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
10000000000000000001
11111111111111111111

*/

#endif