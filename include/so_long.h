/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:22 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/30 10:30:24 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/include/libft.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include "mlx.h"
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define TILE_SIZE 32
# define VALID_CHARS "01CEP"

// Errors
# define ERR_MALLOC "Malloc error\n"
# define ERR_OPEN "Error opening map file\n"
# define ERR_RECTANGLE "Map not rectangular\n"
# define ERR_CHARS "Bad chars in map file\n"
# define ERR_PLAYER "Incorrect player position number\n"
# define ERR_EXIT "Incorrect exit number\n"
# define ERR_COLL "Wrong number of collectibles\n"
# define ERR_MAP_H "Map height of zero\n"

typedef struct s_exit
{
	int	x;
	int y;
} t_exit;

typedef struct s_map
{
	char	**map;
	t_exit	*exit;
	int		exit_count;
	int		coin_count;
	int		p_count;
	int		w;
	int		h;
}			t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		win_w;
	int		win_h;
	void	*sprites[5];
	t_map	*map;
}			t_vars;

void error_handling(char *error_code, t_vars *vars);
void parse_map(const char *filename, t_vars *vars);
int	main(void);

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