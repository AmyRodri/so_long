/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:06:48 by kamys             #+#    #+#             */
/*   Updated: 2025/10/05 22:58:41 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	retantuglar
	cercado de parede = 1
	caracters validos (1, 0, P, C, E)
	quantidades de elementos validos ( P = 1, C >= 1, E >= 1)
	se todos os coletaveis são acesiveis (flodd fill)

int	validate_map(char **map)
{
	if (!map)
		return (0);

	// 1️⃣ Verifica se o mapa é retangular
	if (!check_rectangular(map))
		return (printf("Error: mapa não é retangular\n"), 0);

	// 2️⃣ Verifica se está cercado por paredes
	if (!check_walls(map))
		return (printf("Error: mapa não está cercado por paredes\n"), 0);

	// 3️⃣ Verifica se contém apenas caracteres válidos (1, 0, P, C, E)
	if (!check_valid_chars(map))
		return (printf("Error: mapa contém caracteres inválidos\n"), 0);

	// 4️⃣ Verifica a quantidade de elementos obrigatórios
	if (!check_elements(map)) // 1 P, >=1 C, >=1 E
		return (printf("Error: número incorreto de P, C ou E\n"), 0);

	// 5️⃣ Verifica se todos os coletáveis e saída são acessíveis (flood fill)
	if (!check_reachability(map))
		return (printf("Error: mapa impossível de completar\n"), 0);

	return (1); // ✅ mapa válido
}
*/

static int	check_rectangular(t_map *map)
{
	size_t	len;

	if (!map->grid || !map->grid[0])
		return (erro_int("map is empty\n", 0));
	map->height = 0;
	len = ft_strlen(map->grid[0]);
	while (map->grid[map->height])
	{
		if (len != ft_strlen(map->grid[map->height]))
			return (erro_int("map is not rectangular\n", 0));
		map->height++;
	}
	map->width = len;
	return (1);
}

// static int	check_walls(char **map)
// {
	
// 	return (1);
// }

int	check_map(char *path, t_game *game)
{
	game->map.grid = read_map(path);
	if (!game->map.grid)
		return (0);
	if (!check_rectangular(&game->map))
		return (0);
	print_map(game->map.grid);
	return (1);
}
