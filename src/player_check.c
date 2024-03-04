/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:53:49 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/29 14:54:30 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player_amount(char **map)
{
	int			y;
	int			x;
	static char	player[4];
	int			found;

	player[4] = "NSEW";
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
	static char	player[4];
	int			found;

	player[4] = "NSEW";
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
