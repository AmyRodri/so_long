/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:54:41 by kamys             #+#    #+#             */
/*   Updated: 2025/10/05 23:25:16 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_ber(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (!ft_strncmp(path + (len - 4), ".ber", 4));
}

static int	count_lines(char *path)
{
	char	*line;
	int		fd;
	int		lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (erro_int("could not open the file\n", -1));
	line = get_next_line(fd);
	lines = 0;
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			close(fd);
			return (erro_int("empty line on the map\n", -1));
		}
		free(line);
		lines++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static char	**load_map_content(int lines, char *path)
{
	char	**map;
	char	*line;
	int		len;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (erro_map("could not open the file\n"));
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (erro_map("malloc failed\n"));
	line = get_next_line(fd);
	lines = 0;
	while (line)
	{
		map[lines++] = line;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		line = get_next_line(fd);
	}
	map[lines] = NULL;
	close(fd);
	return (map);
}

char	**read_map(char *path)
{
	int		lines;

	if (!check_ber(path))
		return (erro_map("file must have .ber extension\n"));
	lines = count_lines(path);
	if (lines == -1)
		return (NULL);
	return (load_map_content(lines, path));
}
