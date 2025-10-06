/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/05 22:35:42 by kamys            ###   ########.fr       */
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
	ft_memset(game, 0, sizeof(t_game));
	if (!check_map(args[1], game))
		return (1);
	ft_printf("map sucess\n");
	free_game(game);
	return (0);
}
