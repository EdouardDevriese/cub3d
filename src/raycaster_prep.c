#include "cub3d.h"

// cameraX: x coordinate on plane that represents current x on window (left =
// -1, middle = 0, right = 1) adding player dir vector and plane vector adjusted
// for cameraX results in vector of the ray
void calc_ray(int x, t_ray *r, t_player *p) {
  r->cameraX = 2 * x / (double)WIN_WIDTH - 1;
  r->rayDirX = p->dirX + p->planeX * r->cameraX;
  r->rayDirY = p->dirY + p->planeY * r->cameraX;
}

// deltaDistX: distance ray has to travel to go from one x-side of map square to
// the next deltaDistY: distance ray has to travel to go from one y-side of map
// square to the next
void calc_delta_dist(t_ray *r) {
  if (r->rayDirX == 0) {
    r->deltaDistX = INFINITY;
  } else {
    r->deltaDistX = fabs(1 / r->rayDirX);
  }
  if (r->rayDirY == 0) {
    r->deltaDistY = INFINITY;
  } else {
    r->deltaDistY = fabs(1 / r->rayDirY);
  }
}

// map: coordinates of square ray is currently in
// sideDistX: distance ray has to travel to first next x-side of map square
// sideDistY: distance ray has to travel to first next y-side of map square
// step: sets possible directions for jump to next square (next step)
void calc_side_dist(t_ray *r, t_player p) {
  r->mapX = (int)p.posX;
  r->mapY = (int)p.posY;
  if (r->rayDirX < 0) {
    r->stepX = -1;
    r->sideDistX = (p.posX - r->mapX) * r->deltaDistX;
  } else {
    r->stepX = 1;
    r->sideDistX = (r->mapX + 1.0 - p.posX) * r->deltaDistX;
  }
  if (r->rayDirY < 0) {
    r->stepY = -1;
    r->sideDistY = (p.posY - r->mapY) * r->deltaDistY;
  } else {
    r->stepY = 1;
    r->sideDistY = (r->mapY + 1.0 - p.posY) * r->deltaDistY;
  }
}

// jump to the next square border in the ray's path
// determine how this border is orientated (NO, EA, SO, WE)
// check if square is full or empty
void perform_dda(t_ray *r, int **map) {
  r->hit = 0;
  while (r->hit == 0) {
    if (r->sideDistX < r->sideDistY) {
      r->sideDistX += r->deltaDistX;
      r->mapX += r->stepX;
      r->side = 0;
      if (r->rayDirX > 0)
        r->orientation = WE;
      else
        r->orientation = EA;
    } else {
      r->sideDistY += r->deltaDistY;
      r->mapY += r->stepY;
      r->side = 1;
      if (r->rayDirY > 0)
        r->orientation = SO;
      else
        r->orientation = NO;
    }
    if (map[r->mapX][r->mapY] == 1)
      r->hit = 1;
  }
}

//lineHeight, inverse of distance of the wall (perpWallDist)
//drawStart/drawEnd: highest and lowest pixels to fill with wall (End - Start = lineHeight)
void calc_line_to_draw(t_ray *r, t_drawing *d) {
  if (r->side == 0)
    r->perpWallDist = (r->sideDistX - r->deltaDistX);
  else
    r->perpWallDist = (r->sideDistY - r->deltaDistY);
  d->lineHeight = (int)(WIN_HEIGHT / r->perpWallDist);
  d->drawStart = -d->lineHeight / 2 + WIN_MID;
  if (d->drawStart < 0)
    d->drawStart = 0;
  d->drawEnd = d->lineHeight / 2 + WIN_MID;
  if (d->drawEnd >= WIN_HEIGHT)
    d->drawEnd = WIN_HEIGHT - 1;
}
