/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:32:34 by kamys             #+#    #+#             */
/*   Updated: 2025/10/21 12:36:49 by amyrodri         ###   ########.fr       */
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

static int	get_gradient_color(int top, int bottom, float t)
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;
	int	r;
	int	g;
	int	b;

	r1 = (top >> 16) & 0xFF;
	g1 = (top >> 8) & 0xFF;
	b1 = top & 0xFF;
	r2 = (bottom >> 16) & 0xFF;
	g2 = (bottom >> 8) & 0xFF;
	b2 = bottom & 0xFF;
	r = r1 + t * (r2 - r1);
	g = g1 + t * (g2 - g1);
	b = b1 + t * (b2 - b1);
	return ((r << 16) | (g << 8) | b);
}

static void	draw_sky(t_game *game, int top_color, int bottom_color)
{
	int		y;
	int		x;
	float	t;
	int		color;

	y = 0;
	while (y < game->frame.height)
	{
		t = (float)y / (float)game->frame.height;
		color = get_gradient_color(top_color, bottom_color, t);
		x = 0;
		while (x < game->frame.width)
		{
			put_pixel(&game->frame, x, y, color);
			x++;
		}
		y++;
	}
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
	int	x;
	int	y;
	int	coords[4];

	get_start_end(coords, game);
	y = coords[0];
	while (y < coords[1])
	{
		x = coords[2];
		while (x < coords[3])
		{
			draw_tile(game, game->map.grid[y][x],
				x * TILE - game->cam.x,
				y * TILE - game->cam.y);
			x++;
		}
		y++;
	}
}

void	render_map(t_game *game)
{
	int	draw_x;
	int	draw_y;

	draw_sky(game, 0x001a66, 0x87CEEB);
	render_visible_tiles(game);
	draw_x = (int)(game->player.px * TILE - game->cam.x);
	draw_y = (int)(game->player.py * TILE - game->cam.y);
	draw_tile(game, 'p', draw_x, draw_y);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	print_moves_window(game);
}
