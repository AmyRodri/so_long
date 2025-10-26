/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:38:58 by kamys             #+#    #+#             */
/*   Updated: 2025/10/26 00:53:41 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_sprites_clds(t_game *game)
{
	if (game->sprites.clds.cld_1.ptr)
		mlx_destroy_image(game->mlx, game->sprites.clds.cld_1.ptr);
	if (game->sprites.clds.cld_2.ptr)
		mlx_destroy_image(game->mlx, game->sprites.clds.cld_2.ptr);
	if (game->sprites.clds.cld_3.ptr)
		mlx_destroy_image(game->mlx, game->sprites.clds.cld_3.ptr);
	if (game->sprites.clds.cld_4.ptr)
		mlx_destroy_image(game->mlx, game->sprites.clds.cld_4.ptr);
	if (game->sprites.clds.cld_5.ptr)
		mlx_destroy_image(game->mlx, game->sprites.clds.cld_5.ptr);
	if (game->sprites.clds.cld_6.ptr)
		mlx_destroy_image(game->mlx, game->sprites.clds.cld_6.ptr);
}

static void	free_sprites(t_game *game)
{
	if (game->sprites.player.ptr)
		mlx_destroy_image(game->mlx, game->sprites.player.ptr);
	if (game->sprites.exit.ptr)
		mlx_destroy_image(game->mlx, game->sprites.exit.ptr);
	if (game->sprites.coin.ptr)
		mlx_destroy_image(game->mlx, game->sprites.coin.ptr);
	if (game->sprites.roof.ptr)
		mlx_destroy_image(game->mlx, game->sprites.roof.ptr);
	if (game->sprites.dirt.ptr)
		mlx_destroy_image(game->mlx, game->sprites.dirt.ptr);
	if (game->sprites.floor.ptr)
		mlx_destroy_image(game->mlx, game->sprites.floor.ptr);
	if (game->sprites.walls.wl_1.ptr)
		mlx_destroy_image(game->mlx, game->sprites.walls.wl_1.ptr);
	if (game->sprites.walls.wl_2.ptr)
		mlx_destroy_image(game->mlx, game->sprites.walls.wl_2.ptr);
	free_sprites_clds(game);
}

void	closer(t_game *game)
{
	free_sprites(game);
	mlx_destroy_image(game->mlx, game->frame.ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game(game);
}
