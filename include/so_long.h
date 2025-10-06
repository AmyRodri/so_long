/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:16:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/06 12:32:14 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/srcs/includes/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
	int		direction;
	int		colleted;
}	t_player;

typedef struct s_map
{
	char	**grid;
	char	**visualizer;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
}	t_map;

typedef struct s_game
{
	t_map		map;
	t_player	player;
	int			score;
	int			is_running;
	int			steps;
}	t_game;

// utils.c
void	write_erro(char *s);
int		erro_int(char *s, int exit_code);
char	**erro_map(char *s);
void	free_game(t_game *game);
void	print_map(char **map);

// read_map.c
char	**read_map(char *path);

// check_reachability.c
int		check_reachability(t_map *map, t_player *player);

// check_map.c
int		check_map(char *path, t_game *game);


// main.c
// main

#endif