/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:09:46 by kamys             #+#    #+#             */
/*   Updated: 2025/10/28 22:10:49 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fps_limiter(double current, double fps)
{
	double	frame_end;
	double	frame_duration;
	double	target_frame_time;

	if (fps == 0.0)
		return ;
	frame_end = get_time();
	frame_duration = frame_end - current;
	target_frame_time = 1.0 / fps;
	if (frame_duration < target_frame_time)
		my_usleep(target_frame_time - frame_duration);
}

void	upadate_coin(t_coins *coins)
{
	double	time_now;

	time_now = get_time();
	if (time_now - coins->last_update >= coins->delay)
	{
		coins->cur_frame = (coins->cur_frame + 1) % coins->num_frames;
		coins->last_update = time_now;
	}
}

void	upadate_exit(t_exit *exit)
{
	double	time_now;

	time_now = get_time();
	if (time_now - exit->last_update >= exit->delay)
	{
		exit->cur_frame = (exit->cur_frame + 1) % exit->num_frames;
		exit->last_update = time_now;
	}
}
