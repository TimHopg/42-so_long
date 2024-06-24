/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:22 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/23 19:48:52 by thopgood         ###   ########.fr       */
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

# define MALLOC_FAIL 1

int	main(void);

// Keycodes
enum
{
	KEY_ESC = 53, // 65307 linux
	KEY_W = 13,   //
	KEY_A = 0,    //
	KEY_S = 1,    //
	KEY_D = 2     //
};

// Events
enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

#endif