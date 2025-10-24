/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:16:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/10/24 15:53:53 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/srcs/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdint.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stdlib.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_ESC 65307

# define TILE 32
# define MAX_CLD 10
# define MAX_STAR 100

# define JUMP_FORCE -0.12f
# define GRAVITY 0.003f
# define MAX_FALL_SPEED 0.05f
# define MOVE_SPEED 0.05f

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*ptr;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_cam
{
	float	x;
	float	y;
	int		width;
	int		height;
}	t_cam;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
	int		direction;
	int		collected;
	int		on_ground;
	float	px;
	float	py;
	float	vx;
	float	vy;
	int		left_pressed;
	int		right_pressed;
	int		jump_pressed;
	int		jump_time;
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

typedef struct s_cld
{
	t_img	cld_1;
	t_img	cld_2;
	t_img	cld_3;
	t_img	cld_4;
	t_img	cld_5;
	t_img	cld_6;
}	t_cld;

typedef struct s_cld_itc
{
	int	x;
	int	y;
	int	index;
}	t_cld_itc;

typedef struct s_sprites
{
	t_img	floor;
	t_img	wall;
	t_img	knight;
	t_img	exit;
	t_img	coin;
	t_cld	clds;
}	t_sprites;

typedef struct s_game
{
	t_map		map;
	t_player	player;
	t_sprites	sprites;
	t_img		frame;
	t_cam		cam;
	t_cld_itc	clds[MAX_CLD];
	t_cld_itc	star[MAX_STAR];
	int			num_clds;
	int			num_star;
	void		*mlx;
	void		*win;
}	t_game;

// utils.c
void		write_erro(char *s);
int			erro_int(char *s, int exit_code);
char		**erro_map(char *s);
void		free_game(t_game *game);
void		print_map(char **map);

// utils2.c
int			check_args_and_map(int ac, char **args, t_game **game);
void		print_moves(t_player *p);
double		get_time(void);
void		collect_coin_exit(t_game *game, int x, int y);

// move_vertical.c
void		jumping(t_game *game);
void		gravity_fall(t_game *game);

// move_horizontal.c
void		update_horizontal(t_game *game);

// load_sprites.c
void		load_sprites(t_game *game);

// mlx_utils.c
int			handle_key(int keycode, t_game *game);
int			handle_key_release(int keycode, t_game *game);
int			close_window(void *param);

// update.c
int			update(t_game *game);

// render_map.c
void		render_map(t_game *game);

// draw_tile.c
void		put_pixel(t_img *img, int x, int y, int color);
void		draw_tile(t_game *game, char tile, t_point pt);
void		draw_sprite_to_frame(t_game *game, t_img *sprite, int x, int y);

// draw_sky.c
void		draw_sky(t_game *game, int top_color, int bottom_color);

// moves.c
void		move_player(t_game *game, int x, int y);

// read_map.c
char		**read_map(char *path);

// check_reachability.c
int			check_reachability(t_map *map, t_player *player);

// check_map.c
int			check_map(char *path, t_game *game);

// ft_rand.c
uint32_t	get_init_seed(void);
uint32_t	ft_rand(uint32_t *seed);
uint32_t	ft_rand_range(uint32_t *seed, uint32_t max);

// ft_dtoa.c
char		*ft_dtoa(double n, int decimals);

// inits.c
void		init_all(t_game *game);

// main.c
// main

#endif