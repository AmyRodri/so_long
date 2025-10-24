/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:29:44 by kamys             #+#    #+#             */
/*   Updated: 2025/10/24 13:00:29 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*get_res(char *frac_str, char *int_str)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(int_str, ".");
	res = ft_strjoin(tmp, frac_str);
	free(tmp);
	free(int_str);
	free(frac_str);
	return (res);
}

char	*ft_dtoa(double n, int decimals)
{
	char	*int_str;
	char	*frac_str;
	int		int_part;
	int		frac_part;
	int		multiplier;

	multiplier = 1;
	if (decimals < 0)
		decimals = 0;
	while (decimals--)
		multiplier *= 10;
	int_part = (int)n;
	frac_part = (int)((n - int_part) * multiplier);
	if (frac_part < 0)
		frac_part = -frac_part;
	int_str = ft_itoa(int_part);
	if (multiplier == 1)
		return (int_str);
	frac_str = ft_itoa(frac_part);
	return (get_res(frac_str, int_str));
}
