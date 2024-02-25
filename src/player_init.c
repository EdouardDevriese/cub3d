#include "cub3d.h"

static void set_dir(t_player *p, double dirX, double dirY) {
  p->dirX = dirX;
  p->dirY = dirY;
}

static void set_plane(t_player *p, double planeX, double planeY) {
  p->planeX = planeX;
  p->planeY = planeY;
}

//sets vectors for pos, dir and plane
//dir is just vector up/right/down/left for north/east/south/west
//plane is vector perpendicular to dir, with plane/dir ratio for FOV of 66 degrees
void player_init(t_player *p, t_player_init i) {
  p->posX = (double)i.posX;
  p->posY = (double)i.posY;
  if (i.dir == NO)
  {
    set_dir(p, 0, 1);
    set_plane(p, 0.66, 0);
  }
  else if (i.dir == EA)
  {
    set_dir(p, 1, 0);
    set_plane(p, 0, -0.66);
  }
  else if (i.dir == SO)
  {
    set_dir(p, 0, -1);
    set_plane(p, -0.66, 0);
  }
  else if (i.dir == WE)
  {
    set_dir(p, -1, 0);
    set_plane(p, 0, 0.66);
  }
}