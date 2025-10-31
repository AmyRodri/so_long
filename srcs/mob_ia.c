/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_ia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:52:51 by kamys             #+#    #+#             */
/*   Updated: 2025/10/31 19:11:57 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_check_mob(t_check_mob *check, t_game *game)
{
	t_mob		*mob;

	mob = &game->mob;
	check->map_x = mob->x;
	check->map_y = mob->y;
	check->next_x = check->map_x + (mob->dir * mob->speed);
	if (mob->dir < 0)
		check->front_x = check->next_x;
	else
		check->front_x = check->next_x + TILE - 1;
	check->tx_front = (int)check->front_x / TILE;
	check->top_y = (int)(check->map_y + TILE / 4) / TILE;
	check->mid_y = (int)(check->map_y + TILE / 2) / TILE;
	check->bot_y = (int)(check->map_y + TILE - 1) / TILE;
	check->ty_below_front = (check->map_y + TILE) / TILE;
	check->top = game->map.grid[check->top_y][check->tx_front];
	check->mid = game->map.grid[check->mid_y][check->tx_front];
	check->bot = game->map.grid[check->bot_y][check->tx_front];
}

static int	is_limiter_map(t_game *game, t_check_mob *check)
{
	t_map		*map;
	t_mob		*mob;

	map = &game->map;
	mob = &game->mob;
	if (check->tx_front < 0 || check->tx_front >= map->width
		|| check->top_y < 0 || check->top_y >= map->height
		|| check->mid_y < 0 || check->mid_y >= map->height
		|| check->bot_y < 0 || check->bot_y >= map->height)
	{
		mob->dir *= -1;
		return (0);
	}
	return (1);
}

static int	is_wal_spike(t_check_mob *check, t_mob *mob)
{
	if (check->top == '1' || check->mid == '1' || check->bot == '1'
		|| check->top == 'S' || check->mid == 'S' || check->bot == 'S')
	{
		mob->dir *= -1;
		return (0);
	}
	return (1);
}

static int	is_floor_bellow(t_game *game, t_check_mob *check)
{
	t_map	*map;

	map = &game->map;
	if (check->ty_below_front >= map->height
		|| map->grid[check->ty_below_front][check->tx_front] == '0')
	{
		game->mob.dir *= -1;
		return (0);
	}
	return (1);
}

void	update_mob(t_game *game)
{
	t_check_mob	check;

	init_check_mob(&check, game);
	if (!is_limiter_map(game, &check))
		return ;
	if (!is_wal_spike(&check, &game->mob))
		return ;
	if (!is_floor_bellow(game, &check))
		return ;
	game->mob.x = check.next_x;
}
