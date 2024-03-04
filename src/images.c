/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:20 by vdenisse          #+#    #+#             */
/*   Updated: 2024/03/04 10:02:27 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_image(t_drawing *d, char *path, t_orientation dir, void *mlx)
{
	if (d->tex[dir].img)
		return (1);
	d->tex[dir].img = mlx_xpm_file_to_image(mlx, path, &d->texX, &d->texY);
	if (!d->tex[dir].img)
		d->tex[dir].img = mlx_xpm_file_to_image(mlx,
				"./textures/missing-texture_64x64.xpm", &d->texX, &d->texY);
	d->tex[dir].addr = mlx_get_data_addr(d->tex[dir].img,
			&d->tex[dir].bits_per_pixel, &d->tex[dir].line_length,
			&d->tex[dir].endian);
	if (path)
		free(path);
	return (0);
}

int	check_rgb(char **rgb_strs)
{
	int	i;
	int	j;
	int	status;

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
	if (status || i != 3)
	{
		ft_free_array(rgb_strs, i);
		return (1);
	}
	return (0);
}

int	get_colour(int32_t *colour, char *rgb)
{
	int32_t	rgb_int;
	char	**rgb_strs;

	while (*rgb == ' ')
		rgb++;
	rgb_strs = ft_split(rgb, ',');
	if (check_rgb(rgb_strs))
		return (1);
	rgb_int = rgb_to_int(ft_atoi(rgb_strs[0]), ft_atoi(rgb_strs[1]),
			ft_atoi(rgb_strs[2]));
	*colour = rgb_int;
	ft_free_array(rgb_strs, 3);
	if (rgb)
		free(rgb);
	return (0);
}

int	get_draw_info_line(char *line, t_drawing *d, void *mlx)
{
	char	*path;

	path = ft_strchr(line, ' ');
	path = ft_strtrim(path, " \n");
	if (line[0] == 'N')
		return (get_image(d, path, NO, mlx));
	else if (line[0] == 'S')
		return (get_image(d, path, SO, mlx));
	else if (line[0] == 'W')
		return (get_image(d, path, WE, mlx));
	else if (line[0] == 'E')
		return (get_image(d, path, EA, mlx));
	else if (line[0] == 'F')
		return (get_colour(&d->floor, path));
	else if (line[0] == 'C')
		return (get_colour(&d->ceiling, path));
	else
		return (1);
	return (0);
}

int	get_draw_info(t_drawing *d, void *mlx, char *map_file)
{
	int		fd;
	char	*new_line;
	int		status;

	fd = open(map_file, O_RDONLY);
	new_line = get_next_line(fd);
	set_drawing_to_null(d);
	status = 0;
	while (new_line)
	{
		if (!is_map(new_line) && *new_line != '\n')
			if (!status && get_draw_info_line(new_line, d, mlx))
				status = 1;
		free(new_line);
		new_line = get_next_line(fd);
	}
	return (check_info(d));
}
