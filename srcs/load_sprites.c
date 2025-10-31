/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:11:16 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/30 21:34:01 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_img	load_image(void *mlx, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.ptr)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		exit(erro_int("fail load sprites\n", 1));
	}
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	return (img);
}

static void	load_coins(t_game *game)
{
	int		i;
	char	*path;
	char	*num;
	char	*tmp;
	t_coins	*coins;

	coins = &game->sprites.coins;
	coins->num_frames = MAX_COINS;
	coins->cur_frame = 0;
	coins->last_update = get_time();
	coins->delay = 0.08;
	i = 0;
	while (i < MAX_COINS)
	{
		num = ft_itoa(i);
		tmp = ft_strjoin("assets/coins/coin_", num);
		free(num);
		path = ft_strjoin(tmp, ".xpm");
		free(tmp);
		coins->coins_frame[i] = load_image(game->mlx, path);
		free(path);
		i++;
	}
}

static void	load_exit(t_game *game)
{
	int		i;
	char	*path;
	char	*num;
	char	*tmp;
	t_exit	*exit;

	exit = &game->sprites.exits;
	exit->num_frames = MAX_EXIT;
	exit->cur_frame = 0;
	exit->last_update = get_time();
	exit->delay = 0.1;
	i = 0;
	while (i < MAX_EXIT)
	{
		num = ft_itoa(i);
		tmp = ft_strjoin("assets/exits/exit_", num);
		free(num);
		path = ft_strjoin(tmp, ".xpm");
		free(tmp);
		exit->exit_frame[i] = load_image(game->mlx, path);
		free(path);
		i++;
	}
}

void	load_sprites(t_game *game)
{
	game->sprites.player = load_image(game->mlx, "assets/player.xpm");
	game->sprites.dirt = load_image(game->mlx, "assets/dirt.xpm");
	game->sprites.roof = load_image(game->mlx, "assets/roof.xpm");
	game->sprites.floor = load_image(game->mlx, "assets/floor.xpm");
	game->sprites.spike = load_image(game->mlx, "assets/spike.xpm");
	game->sprites.clds.cld_1 = load_image(game->mlx, "assets/clds/cloud_1.xpm");
	game->sprites.clds.cld_2 = load_image(game->mlx, "assets/clds/cloud_2.xpm");
	game->sprites.clds.cld_3 = load_image(game->mlx, "assets/clds/cloud_3.xpm");
	game->sprites.clds.cld_4 = load_image(game->mlx, "assets/clds/cloud_4.xpm");
	game->sprites.clds.cld_5 = load_image(game->mlx, "assets/clds/cloud_5.xpm");
	game->sprites.clds.cld_6 = load_image(game->mlx, "assets/clds/cloud_6.xpm");
	game->sprites.walls.wl_1 = load_image(game->mlx, "assets/walls/wall_0.xpm");
	game->sprites.walls.wl_2 = load_image(game->mlx, "assets/walls/wall_1.xpm");
	game->sprites.walls.c_1 = load_image(game->mlx, "assets/walls/corne_0.xpm");
	game->sprites.walls.c_2 = load_image(game->mlx, "assets/walls/corne_1.xpm");
	load_exit(game);
	load_coins(game);
}
