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

void	rot_right(t_player *p)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->dir_x;
	p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
	p->dir_y = oldDirX * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
	oldPlaneX = p->plane_x;
	p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
	p->plane_y = oldPlaneX * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
}

void	rot_left(t_player *p)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->dir_x;
	p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
	p->dir_y = oldDirX * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
	oldPlaneX = p->plane_x;
	p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y * sin(-ROT_SPEED);
	p->plane_y = oldPlaneX * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
}
