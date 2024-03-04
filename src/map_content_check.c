/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:18:00 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/29 15:39:15 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_tile(char **map, int y, int x)
{
	if (x == 0 || y == 0)
		return (1);
	if (!map[y][x + 1] || map[y][x + 1] == ' ')
		return (1);
	if (!map[y + 1][x] || map[y + 1][x] == ' ')
		return (1);
	if (!map[y - 1][x] || map[y - 1][x] == ' ')
		return (1);
	if (map[y][x - 1] == ' ')
		return (1);
	return (0);
}
/*
 *for each 0 do a check if its valid
 *it cant be next to a space
 *it cant be on y=0 or x=0
 *it cant be on x=strlen(map[y])
 *y + 1 has to exist and not be a space
 */

int	map_border_check(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '0' && check_tile(map, y, x))
				return (1);
		y++;
	}
	return (0);
}
/*
 *logic idea
 *find a 0
 *start flooding from 0
 *at end of flood,
 *repeat by looking for another 0
 *if no 0
 *    check if any flood is next to any space
 *    if yes
 *        not enclosed
 *
 *        wack
 *
 *BETTER ?
 *loop of entire map once
 *
 */

int	check_map_content(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (map[y][x] != ' ' && map[y][x] != '1' && map[y][x] != '0')
				if (map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != 'E'
					&& map[y][x] != 'W')
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	map_content_check(char **map)
{
	return (check_player_amount(map) || check_map_content(map)
		|| check_player_pos(map) || map_border_check(map));
}
//TODO check if exactly 1 player is present
//TODO walls
