#include "cub3d.h"
#include <stdbool.h>

int	is_map(char *str)
{
	bool has_info;

	has_info = false;
	while (*str && *str != '\n')
	{
		if (*str != '1' && *str != ' ' && *str != '0')
			return (0);
		if (*str == '1' || *str == '0')
			has_info = true;
		str++;
	}
	return (has_info);
}

char	*get_fd(char *map_src, int *fd)
{
	char *line;

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
	if (fd == -1)
		return (1);
	*x = ft_strlen(new_read);
	if (*(x) == 0)
		return (1);
	while (new_read != NULL)
	{
		if (ft_strlen(new_read) > (size_t)*x)
			*x = ft_strlen(new_read);
		(*y)++;
		free(new_read);
		new_read = get_next_line(fd);
	}
	(*x)--;
	close(fd);
	return (1);
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
	new_map = (char **)ft_calloc((y + 1) , sizeof(char *));
	if (!map)
		return (1);
	*map = new_map;
	return (1);
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
	close(fd);
	return (1);
}

#include <stdio.h>

void	print_map(char **map)
{
	while (*map)
	{
		ft_putstr_fd(*map, 1);
		map++;
	}
}

void	get_player_info(t_player_init *i, char **map)
{
	int index = 0;
	char *result;

	result = NULL;
	while (map[index] && !result)
	{
		result = strchr(map[index],'N');
		i->dir = NO;
		if (!result)
		{
			result = strchr(map[index],'E');
			i->dir = EA;
		}
		if (!result)
		{
			result = strchr(map[index],'S');
			i->dir = SO;
		}
		if (!result)
		{
			result = strchr(map[index],'W');
			i->dir = WE;
		}
		if (!result)
			index++;
	}
	i->posY = index;
	i->posX = result - map[index];
}

int	data_init(t_player_init *i, char ***map_src)
{
	int x, y;
	char **map;
	char *map_file = "maps/map.txt";
	
	get_dimensions(map_file, &x, &y);
	malloc_map(&map, y);
	map_to_map(map, map_file, y);


	get_player_info(i, map);

	*map_src = map;

	return (0);
}
//map is forced path atm
//still need to add textures