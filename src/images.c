#include "cub3d.h"

int  get_image(t_drawing *d, char *path, t_orientation dir, void *mlx)
{
	if (d->tex[dir])
	{
		printf("Error texture already exists\n");
		return (0);
	}
	d->tex[dir] = mlx_xpm_file_to_image(mlx, path, &d->texX, &d->texY);
	if (!d->tex[dir])
	{
		printf("Error creating image [%s], in %s\ncreating backup image\n", path, __func__);
		d->tex[dir] = mlx_xpm_file_to_image(mlx, "./textures/missing-texture_64x64.xpm", &d->texX, &d->texY);
		if (!d->tex[dir])
			printf("error creating backup image\n");
	}
	return (0);
}

//TODO create default  value should texture creation fail for any reason

int32_t	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	check_rgb(char **rgb_strs)
{
	int i;
	int j;
	int status;

	status = 0;
	i = 0;
	while (rgb_strs[i])
	{
		j = 0;
		while (!status && rgb_strs[i][j])
			if (!ft_isdigit(rgb_strs[i][j++]))
				status = 1;
		i++;
	}
	if (status)
	{
		ft_free_array(rgb_strs, i);
		printf("Error: Color wrong in %s in %s on line %i\n", __func__, __FILE__, __LINE__);
		return (1);	
	}
	return (0);
}

int  get_colour(int32_t *colour, char *rgb)
{
	int32_t rgb_int;
	char **rgb_strs;

	while (*rgb == ' ')
		rgb++;
	rgb_strs = ft_split(rgb, ',');
	if (check_rgb(rgb_strs))
		return (1);
	rgb_int = rgb_to_int(ft_atoi(rgb_strs[0]), ft_atoi(rgb_strs[1]), ft_atoi(rgb_strs[2]));
	*colour = rgb_int;
	ft_free_array(rgb_strs, 3);
	return (0);
}

int get_draw_info_line(char *line, t_drawing *d, void *mlx)
{
	char *path = ft_strchr(line, ' ');

	path = ft_strtrim(path, " \n");
	if (line[0] == 'N' && get_image(d, path, NO, mlx))
		return (1);
	else if (line[0] == 'S' && get_image(d, path, SO, mlx))
		return (1);
	else if (line[0] == 'W' && get_image(d, path, WE, mlx))
		return (1);
	else if (line[0] == 'E' && get_image(d, path, EA, mlx))
		return (1);
	else if (line[0] == 'F' && get_colour(&d->floor, path))
		return (1);
	else if (line[0] == 'C' && get_colour(&d->ceiling, path))
		return (1);
	return (0);
}

int	check_info(t_drawing *d)
{
	if (!d->tex[NO])
		return (1);
	if (!d->tex[SO])
		return (1);
	if (!d->tex[EA])
		return (1);
	if (!d->tex[WE])
		return (1);
	return (0);
}
//TODO how to check for failure of getting the colour values


void	set_drawing_to_null(t_drawing *d)
{
	d->tex[NO] = 0;
	d->tex[SO] = 0;
	d->tex[WE] = 0;
	d->tex[EA] = 0;
}

int get_draw_info(t_drawing *d, void *mlx)
{
	int fd = open("maps/map.txt", O_RDONLY);
	char *new_line = get_next_line(fd);

	set_drawing_to_null(d);
	while (new_line)
	{
		if (!is_map(new_line) && *new_line != '\n')
			get_draw_info_line(new_line, d, mlx);	
		free(new_line);
		new_line = get_next_line(fd);
	}
	return (0);
}
