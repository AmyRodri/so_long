/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/24 15:33:36 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **args)
{
	t_game	*game;

	if (check_args_and_map(ac, args, &game))
		return (1);
	init_all(game);
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	mlx_hook(game->win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win, 17, 0l, close_window, NULL);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	free_game(game);
	return (0);
}
