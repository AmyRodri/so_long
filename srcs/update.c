/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:55:49 by kamys             #+#    #+#             */
/*   Updated: 2025/10/21 16:50:04 by amyrodri         ###   ########.fr       */
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
	game->cam.y = (game->player.py * TILE) - (game->cam.height / 2);
	if (game->cam.x < 0)
		game->cam.x = 0;
	if (game->cam.y < 0)
		game->cam.y = 0;
	max_x = game->map.width * TILE - game->cam.width;
	max_y = game->map.height * TILE - game->cam.height;
	if (game->cam.x > max_x)
		game->cam.x = max_x;
	if (game->cam.y > max_y)
		game->cam.y = max_y;
}

int	update(t_game *game)
{
	update_pyshical(game);
	update_cam(game);
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
	return (0);
}
