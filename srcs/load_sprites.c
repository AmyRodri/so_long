/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:11:16 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/21 18:00:41 by amyrodri         ###   ########.fr       */
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
	game->sprites.floor = load_image(game->mlx, "assets/floor.xpm");
	game->sprites.wall = load_image(game->mlx, "assets/wall.xpm");
	game->sprites.knight = load_image(game->mlx, "assets/player.xpm");
	game->sprites.exit = load_image(game->mlx, "assets/exit.xpm");
	game->sprites.coin = load_image(game->mlx, "assets/coin_0.xpm");
	game->sprites.clds.cld_1 = load_image(game->mlx, "assets/clds/cloud_1.xpm");
	game->sprites.clds.cld_2 = load_image(game->mlx, "assets/clds/cloud_2.xpm");
	game->sprites.clds.cld_3 = load_image(game->mlx, "assets/clds/cloud_3.xpm");
	game->sprites.clds.cld_4 = load_image(game->mlx, "assets/clds/cloud_4.xpm");
	game->sprites.clds.cld_5 = load_image(game->mlx, "assets/clds/cloud_5.xpm");
	game->sprites.clds.cld_6 = load_image(game->mlx, "assets/clds/cloud_6.xpm");
}
