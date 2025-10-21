/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:09:49 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/21 12:17:41 by amyrodri         ###   ########.fr       */
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
					if (color == 0xFF00FF)
						put_pixel(&game->frame, draw_x, draw_y, 0x00FF00);
					else
						put_pixel(&game->frame, draw_x, draw_y, color);
				}
				px++;
			}
		}
		py++;
	}
}

void	draw_tile(t_game *game, char tile, int x, int y)
{
	if (tile == '1')
		draw_sprite_to_frame(game, &game->sprites.wall, x, y);
	else if (tile == 'C')
		draw_sprite_to_frame(game, &game->sprites.coin, x, y);
	else if (tile == 'E' && game->player.collected == game->map.collectibles)
		draw_sprite_to_frame(game, &game->sprites.exit, x, y);
	else if (tile == 'p')
		draw_sprite_to_frame(game, &game->sprites.knight, x, y);
}
