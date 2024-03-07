/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:21:54 by wdevries          #+#    #+#             */
/*   Updated: 2024/03/07 12:52:52 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jump_x(t_ray *r)
{
	r->sidedist_x += r->deltadist_x;
	r->map_x += r->step_x;
	r->side = 0;
	if (r->raydir_x > 0)
		r->orientation = WE;
	else
		r->orientation = EA;
}

void	jump_y(t_ray *r)
{
	r->sidedist_y += r->deltadist_y;
	r->map_y += r->step_y;
	r->side = 1;
	if (r->raydir_y > 0)
		r->orientation = NO;
	else
		r->orientation = SO;
}

// jump to the next square border in the ray's path
// determine how this border is orientated (NO, EA, SO, WE)
// check if square is full or empty
void	perform_dda(t_ray *r, char **map)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->sidedist_x < r->sidedist_y)
			jump_x(r);
		else
			jump_y(r);
		if (map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}
