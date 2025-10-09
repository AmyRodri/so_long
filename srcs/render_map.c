/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:32:34 by kamys             #+#    #+#             */
/*   Updated: 2025/10/09 13:38:58 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_sprites(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.wall, x * TILE, y * TILE);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.floor, x * TILE, y * TILE);
	if (game->map.grid[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.coin, x * TILE, y * TILE);
	if (game->map.grid[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.exit, x * TILE, y * TILE);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			render_sprites(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->sprites.knight,
		game->player.x * TILE, game->player.y * TILE);
	mlx_string_put(game->mlx, game->win, 10, 10, 0x000000, "moves: ");
	mlx_string_put(game->mlx, game->win, 50, 10, 0x000000,
		ft_itoa(game->player.moves));
}
