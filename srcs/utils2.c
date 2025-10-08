/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:58:43 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/08 11:00:08 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_args_and_map(int ac, char **args, t_game **game)
{
	if (ac != 2)
		return (1);
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (erro_int("malloc", 1));
	ft_bzero(*game, sizeof(t_game));
	if (!check_map(args[1], *game))
		return (1);
	return (0);
}
