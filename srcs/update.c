/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:55:49 by kamys             #+#    #+#             */
/*   Updated: 2025/10/31 02:34:57 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_pyshical(t_game *game)
{
	t_player	*p;

	p = &game->player;
	p->vx = 0;
	if (p->left_pressed)
		p->vx = -MOVE_SPEED;
	if (p->right_pressed)
		p->vx = MOVE_SPEED;
	update_horizontal(game);
	jumping(game);
	gravity_fall(game);
	collect_coin_exit(game, (int)p->px, (int)p->py);
	collect_coin_exit(game, (int)(p->px + 0.9f), (int)(p->py + 0.9f));
}

static void	update_cam(t_game *game)
{
	int	max_x;
	int	max_y;

	game->cam.x = (game->player.px * TILE) - (game->cam.width / 2);
	max_x = game->map.width * TILE - game->cam.width;
	if (game->cam.x > max_x)
		game->cam.x = max_x;
	if (game->cam.x < 0)
		game->cam.x = 0;
	game->cam.y = (game->player.py * TILE) - (game->cam.height / 2);
	max_y = game->map.height * TILE - game->cam.height;
	if (game->cam.y < 0)
		game->cam.y = 0;
	if (game->cam.y > max_y)
		game->cam.y = max_y;
}

int	update(t_game *game)
{
	static double	accumulator = 0.0;
	static double	previos = 0.0;
	double			current;
	double			frame_time;
	const double	tick_rate = 1.0 / 240.0;

	if (previos == 0)
		previos = get_time();
	current = get_time();
	frame_time = current - previos;
	previos = current;
	accumulator += frame_time;
	while (accumulator >= tick_rate)
	{
		update_pyshical(game);
		update_pfra(game);
		update_cam(game);
		upadate_coin(&game->sprites.coins);
		upadate_exit(&game->sprites.exits);
		accumulator -= tick_rate;
	}
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
	fps_limiter(current, 244.0);
	return (0);
}
