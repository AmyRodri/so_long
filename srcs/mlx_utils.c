/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:28:49 by kamys             #+#    #+#             */
/*   Updated: 2025/10/09 13:31:17 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int keycode, void *game)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_D)
		move_player((t_game *)game, 1, 0);
	if (keycode == KEY_A)
		move_player((t_game *)game, -1, 0);
	if (keycode == KEY_W)
		move_player((t_game *)game, 0, -1);
	if (keycode == KEY_S)
		move_player((t_game *)game, 0, 1);
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	gravity_fall(t_game *game)
{
	int	below_y;
	int	x;

	below_y = game->player.y + 1;
	x = game->player.x;
	if (game->map.grid[below_y][x] != '1')
		game->player.y += 1;
}

int	update(t_game *game)
{
	gravity_fall(game);
	render_map(game);
	return (0);
}
