/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:32:34 by kamys             #+#    #+#             */
/*   Updated: 2025/10/12 01:53:51 by kamys            ###   ########.fr       */
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
	free(moves);
	free(str);
}

// static void	draw_background(t_game *game)
// {
// 	int		y;
// 	int		x;

// 	y = 0;
// 	while (game->map.grid[y])
// 	{
// 		x = 0;
// 		while (game->map.grid[y][x])
// 		{
// 			mlx_put_image_to_window(game->mlx, game->win,
// 				game->sprites.floor, x * TILE, y * TILE);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	draw_elements(t_game *game)
// {
// 	int		y;
// 	int		x;

// 	y = 0;
// 	while (game->map.grid[y])
// 	{
// 		x = 0;
// 		while (game->map.grid[y][x])
// 		{
// 			if (game->map.grid[y][x] == '1')
// 				mlx_put_image_to_window(game->mlx, game->win,
// 					game->sprites.wall, x * TILE, y * TILE);
// 			if (game->map.grid[y][x] == 'C')
// 				mlx_put_image_to_window(game->mlx, game->win,
// 					game->sprites.coin, x * TILE, y * TILE);
// 			if (game->map.grid[y][x] == 'E')
// 				mlx_put_image_to_window(game->mlx, game->win,
// 					game->sprites.exit, x * TILE, y * TILE);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(game->mlx, game->win, game->sprites.knight,
// 		(int)game->player.px * TILE, (int)game->player.py * TILE);
// }

// void	render_map(t_game *game)
// {
// 	draw_background(game);
// 	draw_elements(game);
// 	print_moves_window(game);
// }



static void	draw_background(t_game *game)
{
	int start_x = game->cam.x / TILE;
	int start_y = game->cam.y / TILE;
	if (start_x < 0) start_x = 0;
	if (start_y < 0) start_y = 0;

	int end_x = (game->cam.x + game->cam.width) / TILE + 1;
	int end_y = (game->cam.y + game->cam.height) / TILE + 1;
	if (end_x > game->map.width) end_x = game->map.width;
	if (end_y > game->map.height) end_y = game->map.height;

	for (int y = start_y; y < end_y && y < game->map.height; y++)
	{
		if (y < 0 || !game->map.grid[y])
			continue;

		for (int x = start_x; x < end_x && x < game->map.width; x++)
		{
			if (x < 0)
				continue;

			int draw_x = x * TILE - game->cam.x;
			int draw_y = y * TILE - game->cam.y;

			mlx_put_image_to_window(game->mlx, game->win,
				game->sprites.floor, draw_x, draw_y);
		}
	}
}

static void	draw_elements(t_game *game)
{
	int start_x = game->cam.x / TILE;
	int start_y = game->cam.y / TILE;
	if (start_x < 0) start_x = 0;
	if (start_y < 0) start_y = 0;

	int end_x = (game->cam.x + game->cam.width) / TILE + 1;
	int end_y = (game->cam.y + game->cam.height) / TILE + 1;
	if (end_x > game->map.width) end_x = game->map.width;
	if (end_y > game->map.height) end_y = game->map.height;

	for (int y = start_y; y < end_y && y < game->map.height; y++)
	{
		if (y < 0 || !game->map.grid[y])
			continue;

		for (int x = start_x; x < end_x && x < game->map.width; x++)
		{
			if (x < 0)
				continue;

			int draw_x = x * TILE - game->cam.x;
			int draw_y = y * TILE - game->cam.y;

			char tile = game->map.grid[y][x];
			if (tile == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.wall, draw_x, draw_y);
			else if (tile == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.coin, draw_x, draw_y);
			else if (tile == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.exit, draw_x, draw_y);
		}
	}

	int draw_px = (int)((game->player.px * TILE) - game->cam.x);
	int draw_py = (int)((game->player.py * TILE) - game->cam.y);
	mlx_put_image_to_window(game->mlx, game->win, game->sprites.knight, draw_px, draw_py);
}

void	render_map(t_game *game)
{
	draw_background(game);
	draw_elements(game);
	print_moves_window(game);
}
