/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:32:34 by kamys             #+#    #+#             */
/*   Updated: 2025/10/26 00:02:36 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static double	fps(void)
{
	static double	last_time = 0;
	static double	fps = 0;
	static int		frames = 0;
	double			current_time;

	current_time = get_time();
	frames++;
	if (last_time == 0)
		last_time = current_time;
	if (current_time - last_time >= 1.0)
	{
		fps = frames / (current_time - last_time);
		last_time = current_time;
		frames = 0;
	}
	return (fps);
}

static void	str_num(t_game *game, int num, char *str, int x)
{
	char	*moves;
	char	*frase;

	moves = ft_itoa(num);
	frase = ft_strjoin(str, moves);
	mlx_string_put(game->mlx, game->win, x, 10, 0xFFFFFF, frase);
	free(moves);
	free(frase);
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
			draw_tile(game, game->map.grid[pt.y][pt.x], pt, draw_pt);
			pt.x++;
		}
		pt.y++;
	}
	pt.x = (int)(game->player.px * TILE - game->cam.x);
	pt.y = (int)(game->player.py * TILE - game->cam.y);
	draw_sprite_to_frame(game, &game->sprites.player, pt.x, pt.y);
}

void	render_map(t_game *game)
{
	draw_sky(game, 0x001a66, 0x87CEEB);
	render_visible_tiles(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	str_num(game, game->player.moves, "moves: ", 10);
	str_num(game, game->player.collected, "coins: ", 100);
	str_num(game, (int)fps(), "fps: ", 200);
}
