/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:46:00 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/24 15:59:22 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

uint32_t	get_init_seed(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint32_t)(tv.tv_sec ^ tv.tv_usec));
}

uint32_t	ft_rand(uint32_t *seed)
{
	if (*seed == 0)
		*seed = get_init_seed();
	*seed = *seed * 1664525 + 1013904223;
	return (*seed);
}

uint32_t	ft_rand_range(uint32_t *seed, uint32_t max)
{
	return (ft_rand(seed) % max);
}
