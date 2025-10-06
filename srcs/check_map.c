/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:06:48 by kamys             #+#    #+#             */
/*   Updated: 2025/10/06 12:03:16 by amyrodri         ###   ########.fr       */
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
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->grid[y][x];
			if (c != '1' && c != '0' && c != 'P' && c != 'C' && c != 'E')
			{
				ft_printf("linha: %d coluna: %d\n", y, x);
				return (erro_int("invalid character in map\n", 0));
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
				if (map->grid[y][x] != '1')
					return (erro_int("walls invalid\n", 0));
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_elements(t_map *map)
{
	int	y;
	int	x;
	int	p;

	p = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'C')
				map->collectibles++;
			else if (map->grid[y][x] == 'E')
				map->exits++;
			else if (map->grid[y][x] == 'P')
				p++;
			x++;
		}
		y++;
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
