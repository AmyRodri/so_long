/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:37:44 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/21 19:59:29 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <time.h>

static int	get_gradient_color(int top, int bottom, float t)
{
	int	r[3];
	int	g[3];
	int	b[3];

	r[0] = (top >> 16) & 0xFF;
	g[0] = (top >> 8) & 0xFF;
	b[0] = top & 0xFF;
	r[1] = (bottom >> 16) & 0xFF;
	g[1] = (bottom >> 8) & 0xFF;
	b[1] = bottom & 0xFF;
	r[2] = r[0] + t * (r[1] - r[0]);
	g[2] = g[0] + t * (g[1] - g[0]);
	b[2] = b[0] + t * (b[1] - b[0]);
	return ((r[2] << 16) | (g[2] << 8) | b[2]);
}

void	init_clouds(t_game *game)
{
	int	i;

	ft_srand(get_init_seed());
	game->num_clds = 10;
	i = 0;
	while (i < game->num_clds)
	{
		game->clds[i].x = ft_rand() % (game->map.width * TILE - 32);
		game->clds[i].y = ft_rand() % (game->map.height * TILE / 2);
		game->clds[i].index = ft_rand() % 10;
		i++;
	}
	game->num_star = 100;
	i = 0;
	while (i < game->num_star)
	{
		game->star[i].x = ft_rand() % (game->map.width * TILE);
		game->star[i].y = ft_rand() % (game->map.height * TILE / 2);
		game->star[i].index = ft_rand() % 3 + 1;
		i++;
	}
}

static void	draw_stars(t_game *game)
{
	t_point	pt;
	int		i;

	i = 0;
	while (i < game->num_star)
	{
		pt.x = game->star[i].x - game->cam.x / 5;
		pt.y = game->star[i].y - game->cam.y;
		put_pixel(&game->frame, pt.x, pt.y, 0xFFFFFF);
		i++;
	}
}

static void	draw_clouds(t_game *game)
{
	t_img	*sprite;
	int		i;

	i = 0;
	while (i < game->num_clds)
	{
		if (game->clds[i].index == 0)
			sprite = &game->sprites.clds.cld_1;
		else if (game->clds[i].index == 1)
			sprite = &game->sprites.clds.cld_2;
		else if (game->clds[i].index == 2)
			sprite = &game->sprites.clds.cld_3;
		else if (game->clds[i].index == 3)
			sprite = &game->sprites.clds.cld_4;
		else if (game->clds[i].index == 4)
			sprite = &game->sprites.clds.cld_5;
		else
			sprite = &game->sprites.clds.cld_6;
		draw_sprite_to_frame(game, sprite, game->clds[i].x - game->cam.x / 2,
			game->clds[i].y);
		i++;
	}
}

void	draw_sky(t_game *game, int top_color, int bottom_color)
{
	t_point	pt;
	float	t;
	int		color;

	pt.y = 0;
	while (pt.y < game->frame.height)
	{
		t = (float)pt.y / (float)game->frame.height;
		color = get_gradient_color(top_color, bottom_color, t);
		pt.x = 0;
		while (pt.x < game->frame.width)
		{
			put_pixel(&game->frame, pt.x, pt.y, color);
			pt.x++;
		}
		pt.y++;
	}
	draw_stars(game);
	draw_clouds(game);
}
