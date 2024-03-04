/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements_wasd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:08:46 by wdevries          #+#    #+#             */
/*   Updated: 2024/03/04 14:23:33 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_w(t_player *p, char **map)
{
	if (map[(int)(p->pos_y + p->dir_y * MOVE_SPEED)][(int)p->pos_x] == '0')
		p->pos_y += p->dir_y * MOVE_SPEED;
	if (map[(int)p->pos_y][(int)(p->pos_x + p->dir_x * MOVE_SPEED)] == '0')
		p->pos_x += p->dir_x * MOVE_SPEED;
}

void	move_s(t_player *p, char **map)
{
	if (map[(int)(p->pos_y - p->dir_y * MOVE_SPEED)][(int)p->pos_x] == '0')
		p->pos_y -= p->dir_y * MOVE_SPEED;
	if (map[(int)p->pos_y][(int)(p->pos_x - p->dir_x * MOVE_SPEED)] == '0')
		p->pos_x -= p->dir_x * MOVE_SPEED;
}

void	move_a(t_player *p, char **map)
{
	if (map[(int)(p->pos_y - p->plane_y * MOVE_SPEED)][(int)p->pos_x] == '0')
		p->pos_y -= p->plane_y * MOVE_SPEED;
	if (map[(int)p->pos_y][(int)(p->pos_x - p->plane_x * MOVE_SPEED)] == '0')
		p->pos_x -= p->plane_x * MOVE_SPEED;
}

void	move_d(t_player *p, char **map)
{
	if (map[(int)(p->pos_y + p->plane_y * MOVE_SPEED)][(int)p->pos_x] == '0')
		p->pos_y += p->plane_y * MOVE_SPEED;
	if (map[(int)p->pos_y][(int)(p->pos_x + p->plane_x * MOVE_SPEED)] == '0')
		p->pos_x += p->plane_x * MOVE_SPEED;
}
