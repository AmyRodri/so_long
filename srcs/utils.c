/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:31 by kamys             #+#    #+#             */
/*   Updated: 2025/10/31 19:32:53 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	write_erro(char *s)
{
	if (!s)
		s = "Unknown error";
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(s, 2);
}

int	erro_int(char *s, int exit_code)
{
	write_erro(s);
	return (exit_code);
}

char	**erro_map(char *s)
{
	write_erro(s);
	return (NULL);
}

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->map.grid)
	{
		i = 0;
		while (game->map.grid[i])
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	free(game);
}

int	check_collision(t_game *game)
{
	float	player_x;
	float	player_y;
	float	mob_x;
	float	mob_y;

	player_x = game->player.px * TILE;
	player_y = game->player.py * TILE;
	mob_x = game->mob.x;
	mob_y = game->mob.y;
	if (player_x + TILE - 1 < mob_x
		|| player_x > mob_x + TILE - 1
		|| player_y + TILE - 1 < mob_y
		|| player_y > mob_y + TILE - 1)
		return (0);
	return (1);
}
