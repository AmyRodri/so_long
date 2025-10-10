/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:32:34 by kamys             #+#    #+#             */
/*   Updated: 2025/10/09 23:19:44 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_moves_window(t_game *game)
{
	char	*moves;
	char	*str;

	moves = ft_itoa(game->player.moves);
	str = ft_strjoin("moves: ", moves);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, str);
	free(moves);
	free(str);
	moves = ft_itoa(game->player.collected);
	str = ft_strjoin("coins: ", moves);
	mlx_string_put(game->mlx, game->win, 100, 10, 0xFFFFFF, str);
}

static void	draw_background(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->sprites.floor, x * TILE, y * TILE);
			x++;
		}
		y++;
	}
}

static void	draw_elements(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					game->sprites.wall, x * TILE, y * TILE);
			if (game->map.grid[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->sprites.coin, x * TILE, y * TILE);
			if (game->map.grid[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win,
					game->sprites.exit, x * TILE, y * TILE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->sprites.knight,
		(int)game->player.px * TILE, (int)game->player.py * TILE);
}

void	render_map(t_game *game)
{
	draw_background(game);
	draw_elements(game);
	print_moves_window(game);
}
