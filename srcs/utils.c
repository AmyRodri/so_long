/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:31 by kamys             #+#    #+#             */
/*   Updated: 2025/10/05 21:36:38 by kamys            ###   ########.fr       */
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

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
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
