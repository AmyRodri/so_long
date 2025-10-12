/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/12 02:29:06 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_framebuffer(t_game *game)
{
	int	w;
	int	h;

	w = 640;
	h = 384;
	game->frame.ptr = mlx_new_image(game->mlx, w, h);
	game->frame.addr = mlx_get_data_addr(game->frame.ptr, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	game->frame.width = w;
	game->frame.height = h;
}

void	init_cam(t_game *game)
{
	game->cam.width = game->frame.width;
	game->cam.height = game->frame.height;
	game->cam.x = 0;
	game->cam.y = 0;
}

int	main(int ac, char **args)
{
	t_game	*game;

	if (check_args_and_map(ac, args, &game))
		return (1);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 640, 384, "so_long");
	load_sprites(game);
	init_framebuffer(game);
	init_player(&game->player);
	init_cam(game);
	render_map(game);
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	mlx_hook(game->win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win, 17, 0l, close_window, NULL);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	free_game(game);
	return (0);
}
