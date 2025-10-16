/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:28:49 by kamys             #+#    #+#             */
/*   Updated: 2025/10/16 19:32:43 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		game->player.right_pressed = 1;
	if (keycode == KEY_A || keycode == KEY_LEFT)
		game->player.left_pressed = 1;
	if (keycode == KEY_W || keycode == KEY_UP)
		game->player.jump_pressed = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		game->player.right_pressed = 0;
	if (keycode == KEY_A || keycode == KEY_LEFT)
		game->player.left_pressed = 0;
	if (keycode == KEY_W || keycode == KEY_UP)
		game->player.jump_pressed = 0;
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	init_player(t_player *player)
{
	player->px = (float)player->x;
	player->py = (float)player->y;
	player->vx = 0;
	player->vy = 0;
	player->direction = 0;
	player->collected = 0;
	player->on_ground = 0;
	player->left_pressed = 0;
	player->right_pressed = 0;
	player->jump_pressed = 0;
}
