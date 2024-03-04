/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:53:49 by vdenisse          #+#    #+#             */
/*   Updated: 2024/03/04 11:55:05 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player_amount(char **map)
{
	int			y;
	int			x;
	static char	player[4] = "NSEW";
	int			found;

	found = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr(player, map[y][x]))
				found++;
			x++;
		}
		y++;
	}
	if (found == 1)
		return (0);
	return (1);
}

int	check_player_pos(char **map)
{
	int			y;
	int			x;
	static char	player[4] = "NSEW";
	int			found;

	found = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr(player, map[y][x]) && check_tile(map, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

char	*gpt(char *line, t_player_init *i, char p, t_orientation dir)
{
	char	*result;

	result = ft_strchr(line, p);
	if (result)
		i->dir = dir;
	return (result);
}
//get player tile

void	get_player_info(t_player_init *i, char **map)
{
	int		index;
	char	*result;

	index = 0;
	result = NULL;
	while (map[index] && !result)
	{
		result = gpt(map[index], i, 'N', NO);
		if (!result)
			result = gpt(map[index], i, 'E', EA);
		if (!result)
			result = gpt(map[index], i, 'S', SO);
		if (!result)
			result = gpt(map[index], i, 'W', WE);
		if (!result)
			index++;
	}
	i->pos_y = index;
	i->pos_x = result - map[index];
	map[i->pos_y][i->pos_x] = '0';
}
