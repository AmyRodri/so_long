/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:41 by kamys             #+#    #+#             */
/*   Updated: 2025/10/24 15:34:07 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_clouds(t_game *game)
{
	int	i;

	ft_srand(get_init_seed());
	game->num_clds = 10;
	i = 0;
	while (i < game->num_clds)
	{
		game->clds[i].x = ft_rand() % (game->map.width * TILE - 32);
		game->clds[i].y = ft_rand() % (game->map.height * TILE / 2);
		game->clds[i].index = ft_rand() % 6;
		i++;
	}
	game->num_star = 100;
	i = 0;
	while (i < game->num_star)
	{
		game->star[i].x = ft_rand() % (game->map.width * TILE);
		game->star[i].y = ft_rand() % (game->map.height * TILE / 2);
		game->star[i].index = ft_rand() % 3 + 1;
		i++;
	}
}

static void	init_framebuffer(t_game *game)
{
	int	w;
	int	h;

	w = 640;
	h = game->map.height * TILE;
	game->frame.ptr = mlx_new_image(game->mlx, w, h);
	game->frame.addr = mlx_get_data_addr(game->frame.ptr, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	game->frame.width = w;
	game->frame.height = h;
}

static void	init_cam(t_game *game)
{
	game->cam.width = game->frame.width;
	game->cam.height = game->frame.height;
	game->cam.x = 0;
	game->cam.y = 0;
}

static void	init_player(t_player *player)
{
	player->px = (float)player->x;
	player->py = (float)player->y;
	player->vx = 0;
	player->vy = 0;
	player->direction = 0;
	player->collected = 0;
	player->on_ground = 0;
	player->left_pressed = 0;
	player->right_pressed = 0;
	player->jump_pressed = 0;
}

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
