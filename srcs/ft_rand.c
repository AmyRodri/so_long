/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:46:00 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/21 19:44:52 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static uint32_t	g_seed = 0;

uint32_t	get_init_seed(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint32_t)(tv.tv_sec ^ tv.tv_usec));
}

uint32_t	ft_rand(void)
{
	if (g_seed == 0)
		g_seed = get_init_seed();
	g_seed = g_seed * 1664525 + 1013904223;
	return (g_seed);
}

uint32_t	ft_rand_range(uint32_t max)
{
	return (ft_rand() % max);
}

void	ft_srand(uint32_t s)
{
	g_seed = s;
}
