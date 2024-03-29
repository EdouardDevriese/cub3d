/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:09:04 by wdevries          #+#    #+#             */
/*   Updated: 2024/03/04 15:43:26 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_fd(char *map_src, int *fd)
{
	char	*line;

	line = 0;
	*fd = open(map_src, O_RDONLY);
	line = get_next_line(*fd);
	while (line && !is_map(line))
	{
		free(line);
		line = get_next_line(*fd);
	}
	return (line);
}

int	get_dimensions(char *map_src, int *x, int *y)
{
	int		fd;
	char	*new_read;

	*y = 0;
	new_read = get_fd(map_src, &fd);
	if (fd == -1 || !new_read)
		return (1);
	*x = ft_strlen(new_read);
	if (*(x) == 0)
		return (1);
	while (new_read != NULL)
	{
		if (ft_strlen(new_read) > (size_t)(*x))
			*x = ft_strlen(new_read);
		(*y)++;
		free(new_read);
		new_read = get_next_line(fd);
	}
	(*x)--;
	close(fd);
	return (0);
}
/*
 * right now this assumes that the first line is already the map
 * need to make function that somehow skips all first non map lines
 */

int	malloc_map(char ***map, int y)
{
	char	**new_map;
	int		iter;

	iter = 0;
	new_map = *map;
	new_map = (char **)ft_calloc((y + 1), sizeof(char *));
	if (!map)
		return (1);
	*map = new_map;
	return (0);
}

int	map_to_map(char **map, char *map_src, int y)
{
	int		fd;
	char	*new_read;
	int		line;

	line = 0;
	new_read = get_fd(map_src, &fd);
	if (!new_read)
		return (1);
	while (new_read != NULL && line <= y)
	{
		map[line] = new_read;
		new_read = get_next_line(fd);
		line++;
	}
	map[line] = NULL;
	while (new_read)
	{
		free(new_read);
		new_read = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	data_init(t_player_init *i, char ***map_src, char *map_file)
{
	char	**map;
	int		x;
	int		y;

	y = ft_strlen(map_file);
	while (y >= 0 && map_file[y] != '.')
		y--;
	if (y == -1 || ft_strcmp(&map_file[y], ".cub"))
		return (1);
	if (get_dimensions(map_file, &x, &y))
		return (1);
	malloc_map(&map, y);
	if (map_to_map(map, map_file, y))
	{
		ft_free_array(map, y);
		return (1);
	}
	*map_src = map;
	if (map_content_check(map))
	{
		ft_free_array(map, y);
		return (1);
	}
	get_player_info(i, map);
	return (0);
}
