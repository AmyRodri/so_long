/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:32:34 by kamys             #+#    #+#             */
/*   Updated: 2025/10/16 19:07:01 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_moves_window(t_game *game)
{
	char	*moves;
	char	*str;

	moves = ft_itoa(game->player.moves);
	str = ft_strjoin("moves: ", moves);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, str);
	free(moves);
	free(str);
	moves = ft_itoa(game->player.collected);
	str = ft_strjoin("coins: ", moves);
	mlx_string_put(game->mlx, game->win, 100, 10, 0xFFFFFF, str);
	free(moves);
	free(str);
}

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	is_transparent(int color)
{
	return ((color & 0x00FFFFFF) == 0xFF00FF);
}

void	draw_sprite_to_frame(t_game *game, t_img *sprite, int x, int y)
{
	int		px;
	int		py;
	char	*src;
	int		color;
	int		draw_x;
	int		draw_y;

	py = 0;
	while (py < sprite->height)
	{
		draw_y = y + py;
		if (draw_y >= 0 && draw_y < game->frame.height)
		{
			px = 0;
			while (px < sprite->width)
			{
				draw_x = x + px;
				if (draw_x >= 0 && draw_x < game->frame.width)
				{
					src = sprite->addr
						+ (py * sprite->line_len + px * (sprite->bpp / 8));
					color = *(int *)src;
					if (!is_transparent(color))
						put_pixel(&game->frame, draw_x, draw_y, color);
				}
				px++;
			}
		}
		py++;
	}
}

static void	draw_tile(t_game *game, char tile, int x, int y)
{
	if (tile == '1')
		draw_sprite_to_frame(game, &game->sprites.wall, x, y);
	else if (tile == 'C')
		draw_sprite_to_frame(game, &game->sprites.coin, x, y);
	else if (tile == 'E' && game->player.collected == game->map.collectibles)
		draw_sprite_to_frame(game, &game->sprites.exit, x, y);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	draw_x;
	int	draw_y;

	start_x = game->cam.x / TILE;
	start_y = game->cam.y / TILE;
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	end_x = (game->cam.x + game->cam.width) / TILE + 1;
	if (end_x > game->map.width)
		end_x = game->map.width;
	end_y = (game->cam.y + game->cam.height) / TILE + 1;
	if (end_y > game->map.height)
		end_y = game->map.height;
	y = start_y;
	while (y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			draw_x = x * TILE - game->cam.x;
			draw_y = y * TILE - game->cam.y;
			draw_sprite_to_frame(game, &game->sprites.floor, draw_x, draw_y);
			draw_tile(game, game->map.grid[y][x], draw_x, draw_y);
			x++;
		}
		y++;
	}
	draw_x = (int)(game->player.px * TILE - game->cam.x);
	draw_y = (int)(game->player.py * TILE - game->cam.y);
	draw_sprite_to_frame(game, &game->sprites.knight, draw_x, draw_y);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	print_moves_window(game);
}
