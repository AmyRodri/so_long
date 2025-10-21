/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:58:43 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/21 16:46:56 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_args_and_map(int ac, char **args, t_game **game)
{
	if (ac != 2)
		return (1);
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (erro_int("malloc", 1));
	ft_bzero(*game, sizeof(t_game));
	if (!check_map(args[1], *game))
		return (1);
	return (0);
}

void	init_framebuffer(t_game *game)
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

void	init_cam(t_game *game)
{
	game->cam.width = game->frame.width;
	game->cam.height = game->frame.height;
	game->cam.x = 0;
	game->cam.y = 0;
}

void	print_moves(t_player *p)
{
	p->moves++;
	ft_printf("Moves: %d\n", p->moves);
}

void	collect_coin_exit(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == 'C')
	{
		game->player.collected++;
		game->map.grid[y][x] = '0';
		ft_printf("Moedas coletadas: %d\n", game->player.collected);
	}
	if (game->map.grid[y][x] == 'E'
		&& game->player.collected == game->map.collectibles)
		exit(0);
}
