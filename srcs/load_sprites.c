/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:11:16 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/08 16:56:32 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*load_image(void *mlx, char *path)
{
	int		b_w;
	int		b_h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, &b_w, &b_h);
	if (!img)
		exit(erro_int("fail load sprites\n", 1));
	return (img);
}

void	load_sprites(t_game *game)
{
	game->sprites.floor = load_image(game->mlx, "assets/floor.xpm");
	game->sprites.wall = load_image(game->mlx, "assets/wall.xpm");
	game->sprites.knight = load_image(game->mlx, "assets/knight_down_0.xpm");
	game->sprites.exit = load_image(game->mlx, "assets/exit.xpm");
	game->sprites.coin = load_image(game->mlx, "assets/coin_0.xpm");
}
