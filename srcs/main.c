/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/08 15:39:59 by amyrodri         ###   ########.fr       */
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

void render_map(t_game *game)
{
	
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
		render_map(game);
	}
}

int	handle_key(int keycode, void *game)
{
	(void)game;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_D)
		move_player((t_game *)game, 1, 0);
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
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, game->map.width * TILE, game->map.height * TILE, "so_long");

	for (int y = 0; game->map.grid[y]; y++)
	{
		for (int x = 0; game->map.grid[y][x]; x++)
		{
			if (game->map.grid[y][x] == '1')
				draw_tile(mlx, win, x * TILE, y * TILE, 0x888888);
			if (game->map.grid[y][x] == '0')
				draw_tile(mlx, win, x * TILE, y * TILE, 0xFFFFFF);
			if (game->map.grid[y][x] == 'P')
				draw_tile(mlx, win, x * TILE, y * TILE, 0x0000FF);
			if (game->map.grid[y][x] == 'C')
				draw_tile(mlx, win, x * TILE, y * TILE, 0xFFFF00);
			if (game->map.grid[y][x] == 'E')
				draw_tile(mlx, win, x * TILE, y * TILE, 0xFF0000);
		}
	}
	
	mlx_string_put(mlx, win, 10, 10, 0x000000, "moves: ");

	mlx_key_hook(win, handle_key, game);
	mlx_hook(win, 17, 0l, close_window, NULL);
	
	mlx_loop(mlx);
	
	free_game(game);
	return (0);
}
