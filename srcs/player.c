/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 02:27:18 by kamys             #+#    #+#             */
/*   Updated: 2025/10/31 02:35:06 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_sprite_flipped(t_game *game, t_img *sprite, int x, int y)
{
	t_point	frame_pt;
	t_point	sprite_pt;
	t_point	flipped_src;

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
				flipped_src.x = sprite->width - 1 - sprite_pt.x;
				flipped_src.y = sprite_pt.y;
				draw_pixel_safe(game, sprite, frame_pt, flipped_src);
				sprite_pt.x++;
			}
		}
		sprite_pt.y++;
	}
}

void	draw_player(t_game *game, int x, int y)
{
	t_player	*p;
	t_pfra		*pfra;
	t_img		*frame;

	p = &game->player;
	pfra = &game->sprites.player;
	frame = &pfra->idle[0];
	if (p->state == IDLE)
		frame = &pfra->idle[pfra->cur_frame];
	else if (p->state == RUN)
		frame = &pfra->run[pfra->cur_frame];
	else if (p->state == JUMP)
		frame = &pfra->jump[pfra->cur_frame];
	else
		frame = &pfra->fall[pfra->cur_frame];
	if (p->dir == LEFT)
		draw_sprite_flipped(game, frame, x, y);
	else
		draw_sprite_to_frame(game, frame, x, y);
}

void	update_player(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (p->vy < 0)
		p->state = JUMP;
	else if (p->vy > 0)
		p->state = FALL;
	else if (p->vx != 0)
		p->state = RUN;
	else
		p->state = IDLE;
	if (p->vx > 0)
		p->dir = RIGHT;
	else if (p->vx < 0)
		p->dir = LEFT;
}

void	update_pfra(t_game *game)
{
	t_pfra		*pfra;
	double		time_now;
	int			max_frames;

	update_player(game);
	pfra = &game->sprites.player;
	time_now = get_time();
	if (game->player.state == IDLE)
		max_frames = MAX_IDLE;
	else if (game->player.state == RUN)
		max_frames = MAX_RUN;
	else if (game->player.state == JUMP)
		max_frames = MAX_JUMP;
	else
		max_frames = MAX_FALL;
	if (game->player.state == IDLE || game->player.state == RUN)
	{
		if (time_now - pfra->last_update >= pfra->delay)
		{
			pfra->cur_frame = (pfra->cur_frame + 1) % max_frames;
			pfra->last_update = time_now;
		}
	}
	else
		pfra->cur_frame = 0;
}

void	load_player(t_game *game)
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
