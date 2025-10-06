/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reachability.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:06:19 by kamys             #+#    #+#             */
/*   Updated: 2025/10/06 02:31:08 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_grid(t_map *map)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * map->height);
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

static void	flood_fill(char **copy, int x, int y)
{
	if (copy[y][x] == '1' || copy[y][x] == 'F')
		return ;
	copy[y][x] = 'F';
	flood_fill(copy, x + 1, y);
	flood_fill(copy, x - 1, y);
	flood_fill(copy, x, y + 1);
	flood_fill(copy, x, y - 1);
}

int	check_reachability(t_map *map, t_player *player)
{
	char	**copy;
	int		y;
	int		x;

	copy = copy_grid(map);
	if (!copy)
		return (0);
	locate_player(map, player);
	flood_fill(copy, player->x, player->y);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((map->grid[y][x] == 'C' || map->grid[y][x] == 'E')
			&& copy[y][x] != 'F')
			{
				free_copy(copy, map->height);
				return (erro_int("collectibles or inaccessible exit\n", 0));
			}
			x++;
		}
		y++;
	}
	free_copy(copy, map->height);
	return (1);
}
