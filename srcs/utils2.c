/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:58:43 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/24 16:24:40 by kamys            ###   ########.fr       */
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

void	print_moves(t_player *p)
{
	p->moves++;
	ft_printf("Moves: %d\n", p->moves);
}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1000000.0));
}

void	collect_coin_exit(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == 'C')
	{
		game->player.collected++;
		game->map.grid[y][x] = '0';
		ft_printf("Moedas coletadas: %d\n", game->player.collected);
	}
	if (game->map.grid[y][x] == 'E'
		&& game->player.collected == game->map.collectibles)
	{
		closer(game);
		exit(0);
	}
}
