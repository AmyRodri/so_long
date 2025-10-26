/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:11:16 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/26 00:02:20 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_img	load_image(void *mlx, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.ptr)
		exit(erro_int("fail load sprites\n", 1));
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	return (img);
}

void	load_sprites(t_game *game)
{
	game->sprites.player = load_image(game->mlx, "assets/player.xpm");
	game->sprites.exit = load_image(game->mlx, "assets/exit.xpm");
	game->sprites.coin = load_image(game->mlx, "assets/coin_0.xpm");
	game->sprites.dirt = load_image(game->mlx, "assets/dirt.xpm");
	game->sprites.floor = load_image(game->mlx, "assets/floor.xpm");
	game->sprites.roof = load_image(game->mlx, "assets/roof.xpm");
	game->sprites.clds.cld_1 = load_image(game->mlx, "assets/clds/cloud_1.xpm");
	game->sprites.clds.cld_2 = load_image(game->mlx, "assets/clds/cloud_2.xpm");
	game->sprites.clds.cld_3 = load_image(game->mlx, "assets/clds/cloud_3.xpm");
	game->sprites.clds.cld_4 = load_image(game->mlx, "assets/clds/cloud_4.xpm");
	game->sprites.clds.cld_5 = load_image(game->mlx, "assets/clds/cloud_5.xpm");
	game->sprites.clds.cld_6 = load_image(game->mlx, "assets/clds/cloud_6.xpm");
	game->sprites.walls.wl_1 = load_image(game->mlx, "assets/walls/wall_0.xpm");
	game->sprites.walls.wl_2 = load_image(game->mlx, "assets/walls/wall_1.xpm");
}
