/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:48:45 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/21 16:50:41 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	set_x(t_game *game, float next_px)
{
	t_player	*p;
	int			x;

	p = &game->player;
	if (p->vx > 0)
		x = (int)(next_px + 0.9f);
	else
		x = (int)next_px;
	if (x < 0 || x >= game->map.width)
	{
		p->vx = 0;
		return (-1);
	}
	return (x);
}

void	update_horizontal(t_game *game)
{
	t_player	*p;
	float		next_px;
	int			x;
	int			y[2];

	p = &game->player;
	next_px = p->px + p->vx;
	y[0] = (int)p->py;
	y[1] = (int)(p->py + 0.9f);
	x = set_x(game, next_px);
	if (x == -1)
		return ;
	if (game->map.grid[y[0]][x] != '1' && game->map.grid[y[1]][x] != '1')
	{
		if (x != p->x)
			print_moves(p);
		p->px = next_px;
		p->x = x;
		return ;
	}
	p->vx = 0;
}
