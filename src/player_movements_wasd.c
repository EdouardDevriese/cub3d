/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements_wasd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:08:46 by wdevries          #+#    #+#             */
/*   Updated: 2024/03/04 11:17:55 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_w(t_player *p, char **map)
{
	if (map[(int)(p->posY + p->dir_y * MOVE_SPEED)][(int)p->posX] == '0')
		p->posY += p->dir_y * MOVE_SPEED;
	if (map[(int)p->posY][(int)(p->posX + p->dir_x * MOVE_SPEED)] == '0')
		p->posX += p->dir_x * MOVE_SPEED;
}

void	move_s(t_player *p, char **map)
{
	if (map[(int)(p->posY - p->dir_y * MOVE_SPEED)][(int)p->posX] == '0')
		p->posY -= p->dir_y * MOVE_SPEED;
	if (map[(int)p->posY][(int)(p->posX - p->dir_x * MOVE_SPEED)] == '0')
		p->posX -= p->dir_x * MOVE_SPEED;
}

void	move_a(t_player *p, char **map)
{
	if (map[(int)(p->posY - p->plane_y * MOVE_SPEED)][(int)p->posX] == '0')
		p->posY -= p->plane_y * MOVE_SPEED;
	if (map[(int)p->posY][(int)(p->posX - p->plane_x * MOVE_SPEED)] == '0')
		p->posX -= p->plane_x * MOVE_SPEED;
}

void	move_d(t_player *p, char **map)
{
	if (map[(int)(p->posY + p->plane_y * MOVE_SPEED)][(int)p->posX] == '0')
		p->posY += p->plane_y * MOVE_SPEED;
	if (map[(int)p->posY][(int)(p->posX + p->plane_x * MOVE_SPEED)] == '0')
		p->posX += p->plane_x * MOVE_SPEED;
}
