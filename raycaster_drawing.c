#include "cub3d.h"

//wallX: exact location of where ray hits the wall
//texX: x-coordinate of texture we want to draw, based on wallX
void calc_texture_x(t_ray r, t_player p, t_drawing *d) {
      if (r.side == 0)
        d->wallX = p.posY + r.perpWallDist * r.rayDirY;
      else
        d->wallX = p.posX + r.perpWallDist * r.rayDirX;
      d->wallX -= floor(d->wallX);
      d->texX = (int)(d->wallX * (double)TEX_WIDTH);
      if (r.side == 0 && r.rayDirX > 0)
        d->texX = TEX_WIDTH - d->texX - 1;
      if (r.side == 1 && r.rayDirY < 0)
        d->texX = TEX_WIDTH - d->texX - 1;
}
