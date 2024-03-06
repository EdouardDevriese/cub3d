/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:20 by vdenisse          #+#    #+#             */
/*   Updated: 2024/03/06 15:23:40 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_image(t_drawing *d, char *path, t_orientation dir, void *mlx, bool *b)
{
	if (d->tex[dir].img)
		return (1);
	d->tex[dir].img = mlx_xpm_file_to_image(mlx, path, &d->tex_x, &d->tex_y);
	if (!d->tex[dir].img)
		return (1);
	d->tex[dir].addr = mlx_get_data_addr(d->tex[dir].img,
			&d->tex[dir].bits_per_pixel,
			&d->tex[dir].line_length,
			&d->tex[dir].endian);
	if (path)
		free(path);
	if (*b)
		return (1);
	*b = true;
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

int	get_colour(int32_t *colour, char *rgb, bool *b)
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
	if (*b)
		return (1);
	*b = true;
	return (0);
}

int	get_draw_info_line(char *line, t_drawing *d, void *mlx, t_check *check)
{
	char	*path;

	path = ft_strchr(line, ' ');
	path = ft_strtrim(path, " \n");
	if (!ft_strncmp("NO ", line, 3))
		return (get_image(d, path, NO, mlx, &check->no));
	else if (!ft_strncmp("SO ", line, 3))
		return (get_image(d, path, SO, mlx, &check->so));
	else if (!ft_strncmp("WE ", line, 3))
		return (get_image(d, path, WE, mlx, &check->we));
	else if (!ft_strncmp("EA ", line, 3))
		return (get_image(d, path, EA, mlx, &check->ea));
	else if (!ft_strncmp("F ", line, 2))
		return (get_colour(&d->floor, path, &check->f));
	else if (!ft_strncmp("C ", line, 2))
		return (get_colour(&d->ceiling, path, &check->c));
	else
	{
		free(path);
		return (1);
	}
	return (0);
}

t_check check_init(void)
{
	t_check check;
	check.no = false;
	check.so = false;
	check.ea = false;
	check.we = false;
	check.c = false;
	check.f = false;
	return (check);
}

int	get_draw_info(t_drawing *d, void *mlx, char *map_file)
{
	int		fd;
	char	*new_line;
	int		status;
	t_check check;
	int	in_map;

	check = check_init();
	fd = open(map_file, O_RDONLY);
	new_line = get_next_line(fd);
	set_drawing_to_null(d);
	status = 0;
	in_map = 0;
	while (new_line)
	{
		if (is_map(new_line))
			in_map = 1;
		if (!in_map && *new_line != '\n')
			if (!status && get_draw_info_line(new_line, d, mlx, &check))
				status = 1;
		free(new_line);
		new_line = get_next_line(fd);
	}
	return (status || check_info(check));
}
