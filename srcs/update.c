/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:55:49 by kamys             #+#    #+#             */
/*   Updated: 2025/10/09 20:25:33 by kamys            ###   ########.fr       */
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
	if (game->map.grid[y][x] == 'E')
	{
		exit(0);
	}
}

static void	gravity_fall(t_game *game)
{
	float		next_py;
	int			map_x;
	int			new_y;

	next_py = game->player.py + game->player.vy;
	map_x = (int)game->player.px;
	new_y = (int)next_py;
	if (map_x < 0)
		map_x = 0;
	if (map_x >= game->map.width)
		map_x = game->map.width - 1;
	if (new_y < 0)
		new_y = 0;
	if (new_y >= game->map.height)
		new_y = game->map.height - 1;
	game->player.vy += GRAVITY;
	if (game->player.vy > MAX_FALL_SPEED)
		game->player.vy = MAX_FALL_SPEED;
	if (game->map.grid[new_y + 1][map_x] != '1')
	{
		game->player.py = next_py;
		game->player.y = (int)game->player.py;
		game->player.on_ground = 0;
	}
	else
	{
		if (game->player.vy > 0)
			game->player.py = new_y - 1;
		else
			game->player.py = new_y + 1;
		game->player.vy = 0;
		game->player.on_ground = 1;
		game->player.py = new_y;
		game->player.y = new_y;
	}
}

static void	update_horizontal(t_game *game)
{
	t_player	*p;
	float		next_px;
	int			new_x;
	int			map_y;

	p = &game->player;
	next_px = p->px + p->vx;
	new_x = (int)next_px;
	map_y = p->y;
	if (map_y < 0 || map_y >= game->map.height)
		return ;
	if (new_x < 0 || new_x >= game->map.width)
	{
		p->vx = 0;
		return ;
	}
	if (game->map.grid[map_y][new_x] != '1')
	{
		if (new_x != p->x)
			print_moves(p);
		collect_coin_exit(game, new_x, map_y);
		p->px = next_px;
		p->x = new_x;
	}
	else
		p->vx = 0;
}

int	update(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (p->left_pressed)
		p->vx -= 0.05f;
	else if (p->right_pressed)
		p->vx += 0.05f;
	else
		p->vx *= 0.02f;
	p->vx = 0;
	if (p->left_pressed)
		p->vx = -MOVE_SPEED;
	if (p->right_pressed)
		p->vx = MOVE_SPEED;
	update_horizontal(game);
	if (p->jump_pressed && p->on_ground)
	{
		p->vy = JUMP_FORCE;
		p->on_ground = 0;
		print_moves(p);
	}
	gravity_fall(game);
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
	return (0);
}
