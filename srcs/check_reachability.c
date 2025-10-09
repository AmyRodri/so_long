/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reachability.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:06:19 by kamys             #+#    #+#             */
/*   Updated: 2025/10/09 13:13:30 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_grid(t_map *map)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * map->height + 1);
	if (!copy)
		return (erro_map("malloc\n"));
	y = 0;
	while (y < map->height)
	{
		copy[y] = ft_strdup(map->grid[y]);
		if (!copy[y])
		{
			while (--y >= 0)
				free(copy[y]);
			free(copy);
			return (erro_map("strdup\n"));
		}
		y++;
	}
	copy[map->height] = NULL;
	return (copy);
}

static void	free_copy(char **copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(copy[i++]);
	free(copy);
}

static void	locate_player(t_map *map, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'P')
			{
				player->y = y;
				player->x = x;
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	flood_fill(t_map *map, int y, int x, int max_jump)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->visualizer[y][x] == '1' || map->visualizer[y][x] == 'F')
		return ;
	map->visualizer[y][x] = 'F';
	if (y + 1 < map->height && map->visualizer[y + 1][x] != '1')
	{
		flood_fill(map, y + 1, x, max_jump);
		return ;
	}
	if (y + 1 < map->height && map->visualizer[y + 1][x] == '1')
	{
		flood_fill(map, y, x + 1, max_jump);
		flood_fill(map, y, x - 1, max_jump);
	}
	if (y - 1 >= 0 && x + 1 < map->width)
	{
		if (map->visualizer[y - 1][x] != '1'
			&& map->visualizer[y - 1][x + 1] != '1')
		{
			flood_fill(map, y - max_jump, x + 1, max_jump);
			flood_fill(map, y - max_jump, x, max_jump);
			flood_fill(map, y - max_jump, x - 1, max_jump);
		}
	}
}

int	check_reachability(t_map *map, t_player *player)
{
	int		y;
	int		x;

	map->visualizer = copy_grid(map);
	if (!map->visualizer)
		return (0);
	locate_player(map, player);
	flood_fill(map, player->y, player->x, 1);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if ((map->grid[y][x] == 'C' || map->grid[y][x] == 'E')
			&& map->visualizer[y][x] != 'F')
			{
				free_copy(map->visualizer, map->height);
				return (erro_int("collectibles or inaccessible exit\n", 0));
			}
		}
	}
	free_copy(map->visualizer, map->height);
	return (1);
}
