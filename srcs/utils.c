/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:31 by kamys             #+#    #+#             */
/*   Updated: 2025/10/05 22:45:56 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	write_erro(char *s)
{
	if (!s)
		s = "Unknown error";
	write(2, "Error: ", 7);
	write(2, s, ft_strlen(s));
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

void	print_map(char **map)
{
	int	y;
	int	x;

	if (!map)
		return ;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			ft_putchar(map[y][x]);
			x++;
		}
		y++;
	}
}
