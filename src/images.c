#include "cub3d.h"

void get_image(t_drawing *d, char *path, t_orientation dir, void *mlx)
{
	d->tex[dir] = mlx_xpm_file_to_image(mlx, path, &d->texX, &d->texY);
	if (!d->tex[dir])
		printf("Error creating image [%s], in get_image\n", path);
}

void get_colour(t_drawing *d, char *rgb)
{
	char *r;
	r = rgb;
	while (!ft_isdigit(*r))
		r++;
	char *g = ft_strchr(r, ',');
	g++;
	char *b = ft_strchr(g, ',');
	b++;
	r = ft_substr(r, g - r, 0);
	g = ft_substr(g, b - g, 0);
	b = ft_substr(b, ft_strlen(b), 0);
}

int get_draw_info_line(char *line, t_drawing *d, void *mlx)
{
	char *path = ft_strchr(line, ' ');
	t_orientation dir = -1;

	path++;
	if (line[0] == 'N')
		dir = NO;
	if (line[0] == 'S')
		dir = SO;
	if (line[0] == 'W')
		dir = WE;
	if (line[0] == 'E')
		dir = EA;
	if (dir != -1)
		get_image(d, path, dir, mlx);
	else
		get_colour(d, path);
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
