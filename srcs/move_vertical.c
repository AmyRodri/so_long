/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:46:27 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/29 19:08:59 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	colision_jump(t_game *game)
{
	t_player	*p;
	int			left_x;
	int			right_x;
	int			top_y;

	p = &game->player;
	if (p->vy < 0)
	{
		top_y = (int)(p->py - 0.1f);
		left_x = (int)p->px;
		right_x = (int)(p->px + 0.9f);
		if (game->map.grid[top_y][left_x] == '1'
			|| game->map.grid[top_y][right_x] == '1')
		{
			p->vy = 0;
			p->py = top_y + 1.0f;
		}
	}
}

void	jumping(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (p->jump_pressed && p->on_ground)
	{
		if (game->map.grid[(int)p->py - 1][(int)p->px] != '1'
			&& game->map.grid[(int)p->py - 1][(int)(p->px + 0.9f)] != '1')
		{
			p->vy = JUMP_FORCE;
			p->on_ground = 0;
			print_moves(p);
		}
	}
	else if (!p->jump_pressed && p->vy < 0)
		p->vy *= 0.05f;
	colision_jump(game);
}

void	gravity_fall(t_game *game)
{
	t_point		left_right;
	t_player	*p;
	float		next_py;
	int			y;

	p = &game->player;
	p->vy += GRAVITY;
	if (p->vy > MAX_FALL_SPEED)
		p->vy = MAX_FALL_SPEED;
	next_py = p->py + p->vy;
	left_right.x = (int)p->px;
	left_right.y = (int)(p->px + 0.9f);
	y = (int)next_py;
	if (game->map.grid[y + 1][left_right.x] != '1'
		&& game->map.grid[y + 1][left_right.y] != '1')
	{
		p->py = next_py;
		p->on_ground = 0;
		return ;
	}
	p->vy = 0;
	p->on_ground = 1;
	p->py = (float)y;
	p->y = y;
}
