/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:55:49 by kamys             #+#    #+#             */
/*   Updated: 2025/10/09 19:16:31 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_moves(int new_x, t_player *p)
{
	if (new_x != p->x)
	{
		p->moves++;
		ft_printf("Moves: %d\n", p->moves);
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
		print_moves(new_x, p);
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
	if (p->left_pressed)
		p->vx = -MOVE_SPEED;
	if (p->right_pressed)
		p->vx = MOVE_SPEED;
	update_horizontal(game);
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
	return (0);
}
