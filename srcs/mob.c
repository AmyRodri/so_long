/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:44:04 by kamys             #+#    #+#             */
/*   Updated: 2025/10/31 19:08:24 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	locate_mob(t_map *map, t_mob *mob)
{
	t_point	pt;

	pt.y = 0;
	while (pt.y < map->height)
	{
		pt.x = 0;
		while (pt.x < map->width)
		{
			if (map->grid[pt.y][pt.x] == 'M')
			{
				mob->y = pt.y * TILE;
				mob->x = pt.x * TILE;
				map->grid[pt.y][pt.x] = '0';
				return ;
			}
			pt.x++;
		}
		pt.y++;
	}
}

void	init_mob(t_game *game)
{
	t_mob	*mob;

	mob = &game->mob;
	locate_mob(&game->map, mob);
	mob->dir = 1;
	mob->speed = 0.5f;
	mob->active = 1;
}

void	load_mob(t_game *game)
{
	t_mfra	*mob;

	mob = &game->sprites.mob;
	mob->num_frames = MAX_MOB;
	mob->cur_frame = 0;
	mob->last_update = get_time();
	mob->delay = 0.08;
	load_array(game, "assets/mob/mob_", mob->mob_frame, MAX_MOB);
}

void	update_mfra(t_mfra *mob)
{
	double	time_now;

	time_now = get_time();
	if (time_now - mob->last_update >= mob->delay)
	{
		mob->cur_frame = (mob->cur_frame + 1) % mob->num_frames;
		mob->last_update = time_now;
	}
}

void	draw_mob(t_game *game)
{
	t_mfra	*s;
	t_img	*frame;
	int		draw_x;
	int		draw_y;

	s = &game->sprites.mob;
	update_mfra(s);
	frame = s->mob_frame;
	draw_x = (int)game->mob.x - game->cam.x;
	draw_y = (int)game->mob.y - game->cam.y;
	if (game->mob.dir == 1)
		draw_sprite_to_frame(game, &frame[s->cur_frame], draw_x, draw_y);
	else
		draw_sprite_flipped(game, &frame[s->cur_frame], draw_x, draw_y);
}
