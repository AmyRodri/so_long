/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:09:49 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/28 21:50:24 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_pixel_safe(t_game *game, t_img *sprite,
	t_point frame_pt, t_point sprite_pt)
{
	char	*src;
	int		color;

	if (frame_pt.x >= 0 && frame_pt.x < game->frame.width)
	{
		src = sprite->addr
			+ (sprite_pt.y * sprite->line_len
				+ sprite_pt.x * (sprite->bpp / 8));
		color = *(int *)src;
		if (color != 0xFF00FF)
			put_pixel(&game->frame, frame_pt.x, frame_pt.y, color);
	}
}

void	draw_sprite_to_frame(t_game *game, t_img *sprite, int x, int y)
{
	t_point	frame_pt;
	t_point	sprite_pt;

	sprite_pt.y = 0;
	while (sprite_pt.y < sprite->height)
	{
		frame_pt.y = y + sprite_pt.y;
		if (frame_pt.y >= 0 && frame_pt.y < game->frame.height)
		{
			sprite_pt.x = 0;
			while (sprite_pt.x < sprite->width)
			{
				frame_pt.x = x + sprite_pt.x;
				draw_pixel_safe(game, sprite, frame_pt, sprite_pt);
				sprite_pt.x++;
			}
		}
		sprite_pt.y++;
	}
}

static void	draw_wall_floor(t_game *game, t_point pt, t_point draw)
{
	draw_sprite_to_frame(game, &game->sprites.dirt, draw.x, draw.y);
	if (pt.y == 0)
		draw_sprite_to_frame(game, &game->sprites.roof, draw.x, draw.y);
	if (pt.x == 0)
		draw_sprite_to_frame(game, &game->sprites.walls.wl_1, draw.x, draw.y);
	if (pt.x == game->map.width - 1)
		draw_sprite_to_frame(game, &game->sprites.walls.wl_2, draw.x, draw.y);
	if (pt.x == 0 && pt.y == 0)
		draw_sprite_to_frame(game, &game->sprites.walls.c_1, draw.x, draw.y);
	if (pt.x == game->map.width - 1 && pt.y == 0)
		draw_sprite_to_frame(game, &game->sprites.walls.c_2, draw.x, draw.y);
	if (pt.y > 0 && game->map.grid[pt.y - 1][pt.x] != '1')
		draw_sprite_to_frame(game, &game->sprites.floor, draw.x, draw.y);
}

void	draw_tile(t_game *game, char tile, t_point pt, t_point draw)
{
	if (tile == 'C')
		draw_sprite_to_frame(game, &game->sprites.coins.coins_frame[game->sprites.coins.cur_frame], draw.x, draw.y);
	else if (tile == 'E' && game->player.collected == game->map.collectibles)
		draw_sprite_to_frame(game, &game->sprites.exits.exit_frame[game->sprites.exits.cur_frame], draw.x, draw.y);
	else if (tile == '1')
		draw_wall_floor(game, pt, draw);
}
