/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:11:16 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/31 02:22:00 by kamys            ###   ########.fr       */
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

static void	load_array(t_game *game, char *mid_path, t_img *frames, int num_frames)
{
	int		i;
	char	*path;
	char	*num;
	char	*tmp;

	i = 0;
	while (i < num_frames)
	{
		num = ft_itoa(i);
		tmp = ft_strjoin(mid_path, num);
		free(num);
		path = ft_strjoin(tmp, ".xpm");
		free(tmp);
		frames[i] = load_image(game->mlx, path);
		free(path);
		i++;
	}
}

static void	load_coins(t_game *game)
{
	t_coins	*coins;

	coins = &game->sprites.coins;
	coins->num_frames = MAX_COINS;
	coins->cur_frame = 0;
	coins->last_update = get_time();
	coins->delay = 0.08;
	load_array(game, "assets/coins/coin_", coins->coins_frame, MAX_COINS);
}

static void	load_exit(t_game *game)
{
	t_exit	*exit;

	exit = &game->sprites.exits;
	exit->num_frames = MAX_EXIT;
	exit->cur_frame = 0;
	exit->last_update = get_time();
	exit->delay = 0.1;
	load_array(game, "assets/exits/exit_", exit->exit_frame, MAX_EXIT);
}

static void	load_player(t_game *game)
{
	t_pfra	*player;

	player = &game->sprites.player;
	player->num_frames = MAX_EXIT;
	player->cur_frame = 0;
	player->last_update = get_time();
	player->delay = 0.08;
	load_array(game, "assets/player/idle_", player->idle, MAX_IDLE);
	load_array(game, "assets/player/run_", player->run, MAX_RUN);
	load_array(game, "assets/player/jump_", player->jump, MAX_JUMP);
	load_array(game, "assets/player/fall_", player->fall, MAX_FALL);
}

void	load_sprites(t_game *game)
{
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
	load_player(game);
	load_exit(game);
	load_coins(game);
}
