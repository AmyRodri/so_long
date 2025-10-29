/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:12:43 by kamys             #+#    #+#             */
/*   Updated: 2025/10/29 12:44:52 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_coins(t_player *p)
{
	p->collected++;
	ft_printf("\033[1;36m");
	ft_printf("coins: \033[1;37m%d\n", p->collected);
	ft_printf("\033[0m");
}

void	print_moves(t_player *p)
{
	p->moves++;
	ft_printf("\033[1;35m");
	ft_printf("Moves: \033[1;37m%d\n", p->moves);
	ft_printf("\033[0m");
}

void	printf_victory(t_game *game)
{
	ft_printf("\033[1;33m");
	ft_printf("╔══════════════════════════════╗\n");
	ft_printf("║                              ║\n");
	ft_printf("║    \033[1;32m🎉 CONGRATULATIONS! 🎉    \033[1;33m║\n");
	ft_printf("║    \033[1;32mYou reached the exit!     \033[1;33m║\n");
	ft_printf("║                              ║\n");
	ft_printf("║   \033[1;36mMoves:\033[1;37m %d   ", game->player.moves);
	ft_printf("\033[1;36mCoins:\033[1;37m %d / %d  \033[1;33m║\n",
		game->player.collected, game->map.collectibles);
	ft_printf("║                              ║\n");
	ft_printf("╚══════════════════════════════╝\n");
	ft_printf("\033[0m");
}

void	printf_dead(t_game *game)
{
	ft_printf("\033[1;31m");
	ft_printf("╔══════════════════════════════╗\n");
	ft_printf("║                              ║\n");
	ft_printf("║        💀 GAME OVER 💀       ║\n");
	ft_printf("║     You died... again?       ║\n");
	ft_printf("║                              ║\n");
	ft_printf("║   \033[1;36mMoves:\033[1;37m %d   ", game->player.moves);
	ft_printf("\033[1;36mCoins:\033[1;37m %d / %d  \033[1;31m║\n",
		game->player.collected, game->map.collectibles);
	ft_printf("║                              ║\n");
	ft_printf("╚══════════════════════════════╝\n");
	ft_printf("\033[0m");
}

void	print_exit(void)
{
	ft_printf("\033[1;34m");
	ft_printf("╔════════════════════════════════════════╗\n");
	ft_printf("║  🌸 Thanks for playing! See you soon!  ║\n");
	ft_printf("╚════════════════════════════════════════╝\n");
	ft_printf("\033[0m");
}
