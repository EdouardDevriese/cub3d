/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:20 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/29 15:40:23 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_image(t_drawing *d, char *path, t_orientation dir, void *mlx)
{
	if (d->tex[dir].img)
	{
		printf("Error texture already exists\n");
		return (0);
	}
	d->tex[dir].img = mlx_xpm_file_to_image(mlx, path, &d->tex_x, &d->tex_y);
	if (!d->tex[dir].img)
	{
		printf("Error creating image [%s], in %s\ncreating backup image\n",
			path, __func__);
		d->tex[dir].img = mlx_xpm_file_to_image(mlx,
				"./textures/missing-texture_64x64.xpm", &d->tex_x, &d->tex_y);
		if (!d->tex[dir].img)
			printf("error creating backup image\n");
	}
	d->tex[dir].addr = mlx_get_data_addr(d->tex[dir].img,
			&d->tex[dir].bits_per_pixel, &d->tex[dir].line_length,
			&d->tex[dir].endian);
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
		printf("Error: Color wrong in %s in %s on line %i\n", __func__,
			__FILE__, __LINE__);
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
	return (0);
}

int	get_draw_info_line(char *line, t_drawing *d, void *mlx)
{
	char	*path;

	path = ft_strchr(line, ' ');
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

//TODO how to check for failure of getting the colour values
int	get_draw_info(t_drawing *d, void *mlx, char *map_file)
{
	int		fd;
	char	*new_line;

	fd = open(map_file, O_RDONLY);
	new_line = get_next_line(fd);
	set_drawing_to_null(d);
	while (new_line)
	{
		if (!is_map(new_line) && *new_line != '\n')
			get_draw_info_line(new_line, d, mlx);
		free(new_line);
		new_line = get_next_line(fd);
	}
	if (check_info(d))
		printf("Map does not contain all textures\n");
	return (0);
}
