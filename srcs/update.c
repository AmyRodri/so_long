/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:55:49 by kamys             #+#    #+#             */
/*   Updated: 2025/10/16 18:51:48 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_moves(t_player *p)
{
	p->moves++;
	ft_printf("Moves: %d\n", p->moves);
}

static void	collect_coin_exit(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == 'C')
	{
		game->player.collected++;
		game->map.grid[y][x] = '0';
		ft_printf("Moedas coletadas: %d\n", game->player.collected);
	}
	if (game->map.grid[y][x] == 'E'
		&& game->player.collected == game->map.collectibles)
		exit(0);
}

static void	gravity_fall(t_game *game)
{
	t_player	*p;
	float		next_py;
	int			map_x_left;
	int			map_x_right;
	int			map_y;

	p = &game->player;
	next_py = p->py + p->vy;
	map_x_left = (int)p->px;
	map_x_right = (int)(p->px + 1.05f);
	map_y = (int)next_py;
	p->vy += GRAVITY;
	if (p->vy > MAX_FALL_SPEED)
		p->vy = MAX_FALL_SPEED;
	if (game->map.grid[map_y + 1][map_x_left] != '1'
		&& game->map.grid[map_y + 1][map_x_right] != '1')
	{
		p->py = next_py;
		p->y = (int)p->py;
		p->on_ground = 0;
	}
	else
	{
		p->vy = 0;
		p->on_ground = 1;
		p->py = (float)map_y;
		p->y = map_y;
	}
}

static void	update_horizontal(t_game *game)
{
	t_player	*p;
	float		next_px;
	int			map_x;
	int			map_y_top;
	int			map_y_bottom;

	p = &game->player;
	next_px = p->px + p->vx;
	map_y_top = (int)p->py;
	map_y_bottom = (int)(p->py + 0.9f);
	if (p->vx > 0)
		map_x = (int)(next_px + 1.05f);
	else
		map_x = (int)next_px;
	if (map_x < 0 || map_x >= game->map.width)
	{
		p->vx = 0;
		return ;
	}
	if (game->map.grid[map_y_top][map_x] != '1'
		&& game->map.grid[map_y_bottom][map_x] != '1')
	{
		if (map_x != p->x)
			print_moves(p);
		p->px = next_px;
		p->x = map_x;
	}
	else
		p->vx = 0;
}

static void	update_pyshical(t_game *game)
{
	t_player	*p;

	p = &game->player;
	p->vx = 0;
	if (p->left_pressed)
		p->vx = -MOVE_SPEED;
	if (p->right_pressed)
		p->vx = MOVE_SPEED;
	if (p->jump_pressed && p->on_ground)
	{
		if (game->map.grid[p->y - 1][p->x] != '1')
		{
			p->vy = JUMP_FORCE;
			p->on_ground = 0;
			print_moves(p);
		}
	}
	else if (!p->jump_pressed && p->vy < 0)
		p->vy *= 0.05f;
	update_horizontal(game);
	gravity_fall(game);
	collect_coin_exit(game, (int)p->px, (int)p->py);
	collect_coin_exit(game, (int)(p->px + 1.05f), (int)p->py);
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
