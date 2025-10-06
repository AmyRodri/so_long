/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/06 11:51:02 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **args)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (erro_int("malloc", 1));
	ft_bzero(game, sizeof(t_game));
	if (!check_map(args[1], game))
		return (1);
	ft_printf("map sucess\n");
	free_game(game);
	return (0);
}
