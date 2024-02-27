#include "cub3d.h"

int  get_image(t_drawing *d, char *path, t_orientation dir, void *mlx)
{



	d->tex[dir] = mlx_xpm_file_to_image(mlx, path, &d->texX, &d->texY);
	if (!d->tex[dir])
		printf("Error creating image [%s], in %s\n", path, __func__);
	return (0);
}

int32_t	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int  get_colour(int32_t *colour, char *rgb)
{
	int32_t rgb_int;
	while (ft_isdigit(*rgb))
		rgb++;
	char **rgb_strs;
	rgb_strs = ft_split(rgb, ',');
	rgb_int = rgb_to_int(ft_atoi(rgb_strs[0]), ft_atoi(rgb_strs[1]), ft_atoi(rgb_strs[2]));
	*colour = rgb_int;
	return (0);
}

int get_draw_info_line(char *line, t_drawing *d, void *mlx)
{
	char *path = ft_strchr(line, ' ');

	path = ft_strtrim(path, " \n");
	if (line[0] == 'N' && get_image(d, path, NO, mlx))
		return (1);
	if (line[0] == 'S' && get_image(d, path, SO, mlx))
		return (1);
	if (line[0] == 'W' && get_image(d, path, WE, mlx))
		return (1);
	if (line[0] == 'E' && get_image(d, path, EA, mlx))
		return (1);
	if (line[0] == 'F' && get_colour(&d->ceiling, path))
		return (1);
	if (line[0] == 'C' && get_colour(&d->ceiling, path))
		return (1);
	return (0);
}


int get_draw_info(t_drawing *d, void *mlx)
{
	int fd = open("maps/map.txt", O_RDONLY);
	char *new_line = get_next_line(fd);

	while (new_line)
	{
		if (is_map(new_line))
			break ;
		get_draw_info_line(new_line, d, mlx);	
		free(new_line);
		new_line = get_next_line(fd);
	}
	return (0);
}
