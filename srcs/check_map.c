/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:06:48 by kamys             #+#    #+#             */
/*   Updated: 2025/10/30 21:24:14 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_rectangular(t_map *map)
{
	size_t	len;

	if (!map->grid || !map->grid[0])
		return (erro_int("map is empty\n", 0));
	map->height = 0;
	len = ft_strlen(map->grid[0]);
	while (map->grid[map->height])
	{
		if (len != ft_strlen(map->grid[map->height]))
			return (erro_int("map is not rectangular\n", 0));
		map->height++;
	}
	map->width = len;
	return (1);
}

static int	check_valid_char(t_map *map)
{
	t_point	pt;
	char	c;

	pt.y = 0;
	while (pt.y < map->height)
	{
		pt.x = 0;
		while (pt.x < map->width)
		{
			c = map->grid[pt.y][pt.x];
			if (c != '1' && c != '0' && c != 'P' && c != 'C' && c != 'E'
				&& c != 'S')
				return (erro_int("invalid character in map\n", 0));
			pt.x++;
		}
		pt.y++;
	}
	return (1);
}

static int	check_walls(t_map *map)
{
	t_point	pt;

	pt.y = 0;
	while (pt.y < map->height)
	{
		pt.x = 0;
		while (pt.x < map->width)
		{
			if (pt.y == 0 || pt.y == map->height - 1
				|| pt.x == 0 || pt.x == map->width - 1)
				if (map->grid[pt.y][pt.x] != '1')
					return (erro_int("walls invalid\n", 0));
			pt.x++;
		}
		pt.y++;
	}
	return (1);
}

static int	check_elements(t_map *map)
{
	t_point	pt;
	int		p;

	p = 0;
	pt.y = 0;
	while (pt.y < map->height)
	{
		pt.x = 0;
		while (pt.x < map->width)
		{
			if (map->grid[pt.y][pt.x] == 'C')
				map->collectibles++;
			else if (map->grid[pt.y][pt.x] == 'E')
				map->exits++;
			else if (map->grid[pt.y][pt.x] == 'P')
				p++;
			pt.x++;
		}
		pt.y++;
	}
	if (p != 1 || map->collectibles < 1 || map->exits != 1)
		return (erro_int("invalid element count\n", 0));
	return (1);
}

int	check_map(char *path, t_game *game)
{
	game->map.grid = read_map(path);
	if (!game->map.grid)
		return (0);
	if (!check_rectangular(&game->map))
		return (0);
	if (!check_valid_char(&game->map))
		return (0);
	if (!check_walls(&game->map))
		return (0);
	if (!check_elements(&game->map))
		return (0);
	if (!check_reachability(&game->map, &game->player))
		return (0);
	return (1);
}
