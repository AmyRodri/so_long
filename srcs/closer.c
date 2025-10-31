/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:38:58 by kamys             #+#    #+#             */
/*   Updated: 2025/10/30 21:42:20 by kamys            ###   ########.fr       */
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

static void	free_sprite_array(void *mlx, t_img *sprite, int num_frame)
{
	int	i;

	i = 0;
	while (i < num_frame)
	{
		if (sprite[i].ptr)
			mlx_destroy_image(mlx, sprite[i].ptr);
		i++;
	}
}

static void	free_sprites(t_game *game)
{
	if (game->sprites.player.ptr)
		mlx_destroy_image(game->mlx, game->sprites.player.ptr);
	if (game->sprites.dirt.ptr)
		mlx_destroy_image(game->mlx, game->sprites.dirt.ptr);
	if (game->sprites.roof.ptr)
		mlx_destroy_image(game->mlx, game->sprites.roof.ptr);
	if (game->sprites.floor.ptr)
		mlx_destroy_image(game->mlx, game->sprites.floor.ptr);
	if (game->sprites.spike.ptr)
		mlx_destroy_image(game->mlx, game->sprites.spike.ptr);
	if (game->sprites.walls.wl_1.ptr)
		mlx_destroy_image(game->mlx, game->sprites.walls.wl_1.ptr);
	if (game->sprites.walls.wl_2.ptr)
		mlx_destroy_image(game->mlx, game->sprites.walls.wl_2.ptr);
	if (game->sprites.walls.c_1.ptr)
		mlx_destroy_image(game->mlx, game->sprites.walls.c_1.ptr);
	if (game->sprites.walls.c_2.ptr)
		mlx_destroy_image(game->mlx, game->sprites.walls.c_2.ptr);
	free_sprites_clds(game);
	free_sprite_array(game->mlx, game->sprites.coins.coins_frame, MAX_COINS);
	free_sprite_array(game->mlx, game->sprites.exits.exit_frame, MAX_EXIT);
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
