/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:27 by thopgood          #+#    #+#             */
/*   Updated: 2024/07/11 17:59:41 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Function initialises fields of t_map structure
 */

void	initialise_map(t_vars *vars, char *map_str)
{
	vars->map = ft_calloc(1, sizeof(t_map));
	if (vars->map == NULL)
		error_handling_vars(ERR_MALLOC, vars); // !
	vars->map->map_str = map_str;
}

/*
 * Saves map dimensions into structure
 */

void	map_dimensions(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map->map[i])
		i++;
	vars->map->h = i;
	vars->map->w = ft_strlen(vars->map->map[0]);
}

/*
 * Converts .ber map file into single malloc'd string
 */

char	*mapfile_to_str(int fd)
{
	char	*temp;
	char	*line;
	int		gnl_status;
	char	*map_str;

	map_str = ft_strdup("");
	if (map_str == NULL)
		error_handling_import(ERR_MALLOC, NULL, NULL);
	gnl_status = get_next_line(fd, &line);
	while (gnl_status > 0)
	{
		temp = map_str;
		map_str = ft_strjoin(map_str, line);
		if (map_str == NULL)
			error_handling_import(ERR_MALLOC, temp, line);
		free(temp);
		free(line);
		gnl_status = get_next_line(fd, &line);
	}
	if (gnl_status == GNL_ERROR)
		error_handling_import(ERR_GNL, map_str, NULL);
	return (map_str);
}

/*
 * Parses map. Creates map string from map file. Then creates vector from
 * map string. Stores map dimensions in map struct. Checks validity of map.
 */

void	parse_map(int fd, t_vars *vars)
{
	char	*map_str;

	map_str = mapfile_to_str(fd);
	initialise_map(vars, map_str);
	vars->map->map = ft_split(vars->map->map_str, '\n');
	if (vars->map->map == NULL)
		error_handling_import(ERR_MALLOC, vars->map->map_str, NULL);
	if (!vars->map->map[0])
		error_handling_vars(ERR_MAP_H, vars);
	map_dimensions(vars);
	// print_map(vars);
	is_map_valid(vars);
	// print_map(vars);
}

/*
 * Map errors:
 * non rectangular (lines different length)
 * bad chars
 * flood fill fail
 * less or more than 1 exit
 * less or more than 1 starting position
 * less than one collectible
 * file permissions
 * wall not around perimeter
 * empty map
 * map of new lines
 * map must be of type .ber
 */
