/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:22 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/28 16:29:39 by thopgood         ###   ########.fr       */
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

# define MALLOC_FAIL 1
# define OPEN_FAIL 2

# define TILE_SIZE 32



typedef struct s_exit
{
	int	x;
	int y;
} t_exit;

typedef struct s_map
{
	char	**map;
	t_exit	*exit;
	int		coins;
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

#endif