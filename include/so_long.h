/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:16:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/05 21:54:15 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/srcs/includes/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

// utils.c
void	write_erro(char *s);
int		erro_int(char *s, int exit_code);
char	**erro_map(char *s);
void	free_map(char **map);
void	print_map(char **map);

// read_map.c
char	**read_map(char *path);

// check_map.c
int		check_map(char *path_map, char ***map);


// main.c
// main

#endif