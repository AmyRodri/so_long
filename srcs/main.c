/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/23 04:36:54 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_all(t_game *game)
{
	int	height;
	int	width;

	game->mlx = mlx_init();
	if ((game->map.width * TILE) < 640)
		width = game->map.width * TILE;
	else
		width = 640;
	if ((game->map.height * TILE) > 1000)
		exit(erro_int("map height\n", 1));
	else
		height = game->map.height * TILE;
	game->win = mlx_new_window(game->mlx, width, height, "so_long");
	load_sprites(game);
	init_framebuffer(game);
	init_player(&game->player);
	init_cam(game);
	init_clouds(game);
}

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
