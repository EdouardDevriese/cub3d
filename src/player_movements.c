#include "cub3d.h"

void	move_w(t_player *p, char **map)
{
	if (map[(int)(p->posY + p->dirY * MOVE_SPEED)][(int)p->posX] == '0')
		p->posY += p->dirY * MOVE_SPEED;
	if (map[(int)p->posY][(int)(p->posX + p->dirX * MOVE_SPEED)] == '0')
		p->posX += p->dirX * MOVE_SPEED;
}

void	move_s(t_player *p, char **map)
{
	if (map[(int)(p->posY - p->dirY * MOVE_SPEED)][(int)p->posX] == '0')
		p->posY -= p->dirY * MOVE_SPEED;
	if (map[(int)p->posY][(int)(p->posX - p->dirX * MOVE_SPEED)] == '0')
		p->posX -= p->dirX * MOVE_SPEED;
}

void	move_a(t_player *p, char **map)
{
	if (map[(int)(p->posY - p->planeY * MOVE_SPEED)][(int)p->posX] == '0')
		p->posY -= p->planeY * MOVE_SPEED;
	if (map[(int)p->posY][(int)(p->posX - p->planeX * MOVE_SPEED)] == '0')
		p->posX -= p->planeX * MOVE_SPEED;
}

void	move_d(t_player *p, char **map)
{
	if (map[(int)(p->posY + p->planeY * MOVE_SPEED)][(int)p->posX] == '0')
		p->posY += p->planeY * MOVE_SPEED;
	if (map[(int)p->posY][(int)(p->posX + p->planeX * MOVE_SPEED)] == '0')
		p->posX += p->planeX * MOVE_SPEED;
}

void	rot_right(t_player *p)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->dirX;
	p->dirX = p->dirX * cos(ROT_SPEED) - p->dirY * sin(ROT_SPEED);
	p->dirY = oldDirX * sin(ROT_SPEED) + p->dirY * cos(ROT_SPEED);
	oldPlaneX = p->planeX;
	p->planeX = p->planeX * cos(ROT_SPEED) - p->planeY * sin(ROT_SPEED);
	p->planeY = oldPlaneX * sin(ROT_SPEED) + p->planeY * cos(ROT_SPEED);
}

void	rot_left(t_player *p)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->dirX;
	p->dirX = p->dirX * cos(-ROT_SPEED) - p->dirY * sin(-ROT_SPEED);
	p->dirY = oldDirX * sin(-ROT_SPEED) + p->dirY * cos(-ROT_SPEED);
	oldPlaneX = p->planeX;
	p->planeX = p->planeX * cos(-ROT_SPEED) - p->planeY * sin(-ROT_SPEED);
	p->planeY = oldPlaneX * sin(-ROT_SPEED) + p->planeY * cos(-ROT_SPEED);
}
