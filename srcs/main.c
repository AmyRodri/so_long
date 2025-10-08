/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/08 16:55:52 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define TILE 32
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

void	draw_tile(void *mlx, void *win, int x, int y, int color);

void	render_map(t_game *game)
{
	for (int y = 0; game->map.grid[y]; y++)
	{
		for (int x = 0; game->map.grid[y][x]; x++)
		{
			if (game->map.grid[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.wall, x * TILE, y * TILE);
			else
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.floor, x * TILE, y * TILE);
			if (game->map.grid[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.coin, x * TILE, y * TILE);
			if (game->map.grid[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.exit, x * TILE, y * TILE);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->sprites.knight, game->player.x * TILE, game->player.y * TILE);
}

void	move_player(t_game *game, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = game->player.x + x;
	new_y = game->player.y + y;
	if (game->map.grid[new_y][new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.moves++;
		ft_printf("moves: %d\n", game->player.moves);
		mlx_clear_window(game->mlx, game->win);
		render_map(game);
	}
}

int	handle_key(int keycode, void *game)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_D)
		move_player((t_game *)game, 1, 0);
	if (keycode == KEY_A)
		move_player((t_game *)game, -1, 0);
	if (keycode == KEY_W)
		move_player((t_game *)game, 0, -1);
	if (keycode == KEY_S)
		move_player((t_game *)game, 0, 1);
	return (0);
}

void	draw_tile(void *mlx, void *win, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE)
	{
		j = 0;
		while (j < TILE)
		{
			mlx_pixel_put(mlx, win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(int ac, char **args)
{
	t_game	*game;

	if (check_args_and_map(ac, args, &game))
		return (1);
	ft_printf("map sucess\n");
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map.width * TILE, game->map.height * TILE, "so_long");

	load_sprites(game);
	
	render_map(game);
	
	mlx_string_put(game->mlx, game->win, 10, 10, 0x000000, "moves: ");

	mlx_key_hook(game->win, handle_key, game);
	mlx_hook(game->win, 17, 0l, close_window, NULL);
	
	mlx_loop(game->mlx);
	
	free_game(game);
	return (0);
}
