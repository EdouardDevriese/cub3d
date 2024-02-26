#include "../libft/inc/libft.h"
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
		if (ft_strlen(new_read) > *x)
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

int	malloc_map(char ***map, int x, int y)
{
	char	**new_map;
	int		iter;

	iter = 0;
	new_map = *map;
	new_map = (char **)ft_calloc((y + 1) , sizeof(char *));
	if (!map)
		return (1);
	new_map[y] = NULL;
	*map = new_map;
	return (1);
}

int	line_to_map(char **map, char *new_read, int y, int max_x)
{
	int	x;
	int	len;

	len = ft_strlen(new_read);
	x = 0;
	while (x < max_x)
	{
		if (x >= len - 1 || new_read[x] == ' ')
			map[y][x] = ' ';
		else
			map[y][x] = new_read[x];
		x++;
	}
	return (0);
}

int	map_to_map(char **map, char *map_src, int x, int y)
{
	int		fd;
	char	*new_read;
	int		line;

	line = 0;
	new_read = get_fd(map_src, &fd);
	if (!new_read)
		return (1);
	while (new_read != NULL)
	{
		line_to_map(map, new_read, line, x);
		free(new_read);
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
		ft_putendl_fd(*map, 1);
		map++;
	}
}
int	main(void)
{
	int x, y;
	char **map;
	char *map_src = "map.txt";
	
	get_dimensions(map_src, &x, &y);
	printf("x [%i] ; y [%i]", x, y);
	malloc_map(&map, x, y);
	map_to_map(map, map_src, x, y);
	print_map(map);
}
