/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:28:49 by kamys             #+#    #+#             */
/*   Updated: 2025/10/25 00:24:58 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		print_exit();
		closer(game);
		exit(0);
	}
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
	print_exit();
	closer((t_game *)param);
	exit(0);
	return (0);
}
