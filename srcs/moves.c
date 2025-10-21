/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:33:54 by kamys             #+#    #+#             */
/*   Updated: 2025/10/21 15:54:47 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = game->player.x + x;
	new_y = game->player.y + y;
	if (game->map.grid[new_y][new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.moves++;
		ft_printf("moves: %d\n", game->player.moves);
	}
}
