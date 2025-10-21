/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:32:34 by kamys             #+#    #+#             */
/*   Updated: 2025/10/21 16:08:01 by amyrodri         ###   ########.fr       */
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

static void	get_start_end(int *coords, t_game *game)
{
	coords[0] = game->cam.y / TILE;
	if (coords[0] < 0)
		coords[0] = 0;
	coords[1] = (game->cam.y + game->cam.height) / TILE + 1;
	if (coords[1] > game->map.height)
		coords[1] = game->map.height;
	coords[2] = game->cam.x / TILE;
	if (coords[2] < 0)
		coords[2] = 0;
	coords[3] = (game->cam.x + game->cam.width) / TILE + 1;
	if (coords[3] > game->map.width)
		coords[3] = game->map.width;
}

static void	render_visible_tiles(t_game *game)
{
	t_point	pt;
	t_point	draw_pt;
	int		coords[4];

	get_start_end(coords, game);
	pt.y = coords[0];
	while (pt.y < coords[1])
	{
		pt.x = coords[2];
		while (pt.x < coords[3])
		{
			draw_pt.x = pt.x * TILE - game->cam.x;
			draw_pt.y = pt.y * TILE - game->cam.y;
			draw_tile(game, game->map.grid[pt.y][pt.x], draw_pt);
			pt.x++;
		}
		pt.y++;
	}
}

void	render_map(t_game *game)
{
	t_point	pt;

	draw_sky(game, 0x001a66, 0x87CEEB);
	render_visible_tiles(game);
	pt.x = (int)(game->player.px * TILE - game->cam.x);
	pt.y = (int)(game->player.py * TILE - game->cam.y);
	draw_tile(game, 'p', pt);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	print_moves_window(game);
}
