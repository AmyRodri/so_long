/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:58:43 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/31 15:42:03 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_args_and_map(int ac, char **args, t_game **game)
{
	if (ac != 2)
		return (1);
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (erro_int("malloc", 1));
	ft_bzero(*game, sizeof(t_game));
	if (!check_map(args[1], *game))
		return (1);
	return (0);
}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1000000.0));
}

void	my_usleep(double seconds)
{
	double	start;
	double	end;

	start = get_time();
	end = get_time();
	while (end - start < seconds)
		end = get_time();
}

int	check_floof_fill(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (0);
	if (map->visualizer[y][x] == '1' || map->visualizer[y][x] == 'F'
		|| map->visualizer[y][x] == 'S' || map->visualizer[y][x] == 'M')
		return (0);
	map->visualizer[y][x] = 'F';
	return (1);
}

void	collect_coin_exit(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == 'C')
	{
		game->map.grid[y][x] = '0';
		print_coins(&game->player);
	}
	if (game->map.grid[y][x] == 'E'
		&& game->player.collected == game->map.collectibles)
	{
		printf_victory(game);
		closer(game);
		exit(0);
	}
	if (game->map.grid[y][x] == 'S')
	{
		printf_dead(game);
		closer(game);
		exit(0);
	}
}
