/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements_rot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:16:05 by wdevries          #+#    #+#             */
/*   Updated: 2024/03/07 14:04:10 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_left(t_player *p)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
	p->dir_y = old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
	p->plane_y = old_plane_x * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
}

void	rot_right(t_player *p)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
	p->dir_y = old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y * sin(-ROT_SPEED);
	p->plane_y = old_plane_x * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
}
