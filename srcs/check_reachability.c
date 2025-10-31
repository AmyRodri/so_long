/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reachability.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:06:19 by kamys             #+#    #+#             */
/*   Updated: 2025/10/30 21:28:11 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	copy_grid(t_map *map)
{
	int		y;

	map->visualizer = malloc(sizeof(char *) * (map->height + 1));
	if (!map->visualizer)
		return (erro_int("malloc\n", 0));
	y = 0;
	while (y < map->height)
	{
		map->visualizer[y] = ft_strdup(map->grid[y]);
		if (!map->visualizer[y])
		{
			while (--y >= 0)
				free(map->visualizer[y]);
			free(map->visualizer);
			return (erro_int("strdup\n", 0));
		}
		y++;
	}
	map->visualizer[map->height] = NULL;
	return (1);
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
	t_point	pt;

	pt.y = 0;
	while (pt.y < map->height)
	{
		pt.x = 0;
		while (pt.x < map->width)
		{
			if (map->grid[pt.y][pt.x] == 'P')
			{
				player->y = pt.y;
				player->x = pt.x;
				return ;
			}
			pt.x++;
		}
		pt.y++;
	}
}

static void	flood_fill(t_map *map, int y, int x, int max_jump)
{
	int	ny;
	int	jump;

	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->visualizer[y][x] == '1' || map->visualizer[y][x] == 'F'
		|| map->visualizer[y][x] == 'S')
		return ;
	map->visualizer[y][x] = 'F';
	if (y + 1 < map->height && map->visualizer[y + 1][x] != '1')
	{
		flood_fill(map, y + 1, x, max_jump);
		flood_fill(map, y + 1, x + 1, max_jump);
		flood_fill(map, y + 1, x - 1, max_jump);
		return ;
	}
	flood_fill(map, y, x + 1, max_jump);
	flood_fill(map, y, x - 1, max_jump);
	jump = 1;
	ny = y - jump;
	while (jump <= max_jump && ny >= 0 && map->visualizer[ny][x] != '1')
	{
		if (map->visualizer[ny][x] != 'F')
			map->visualizer[ny][x] = 'F';
		flood_fill(map, ny, x + 1, max_jump);
		flood_fill(map, ny, x - 1, max_jump);
		jump++;
		ny = y - jump;
	}
}

int	check_reachability(t_map *map, t_player *player)
{
	t_point	pt;

	if (!copy_grid(map))
		return (0);
	locate_player(map, player);
	flood_fill(map, player->y, player->x, 2);
	pt.y = 0;
	while (pt.y < map->height)
	{
		pt.x = 0;
		while (pt.x < map->width)
		{
			if ((map->grid[pt.y][pt.x] == 'C' || map->grid[pt.y][pt.x] == 'E')
			&& map->visualizer[pt.y][pt.x] != 'F')
			{
				free_copy(map->visualizer, map->height);
				return (erro_int("collectibles or locked exit\n", 0));
			}
			pt.x++;
		}
		pt.y++;
	}
	free_copy(map->visualizer, map->height);
	return (1);
}
