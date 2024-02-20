#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_MID 240
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#include <math.h>

typedef enum e_orientation { NO, SO, WE, EA } t_orientation;

typedef struct s_player_init {
  int posX;
  int posY;
  t_orientation dir;
} t_player_init;

// pos: vector of the player
// dir: vector of player direction
// plane: vector of camera plane
//->set plane perpendicular to dir
//->plane to dir ratio determines FOV
// orientation: easier for setup, will determine dir vector
typedef struct s_player {
  double posY;
  double posX;
  double dirY;
  double dirX;
  double planeX;
  double planeY;
  t_orientation orientation;
} t_player;

typedef struct s_ray {
  double cameraX;
  double rayDirX;
  double rayDirY;
  int mapX;
  int mapY;
  double sideDistX;
  double sideDistY;
  double deltaDistX;
  double deltaDistY;
  double perpWallDist;
  int stepX;
  int stepY;
  int hit;
  int side;
  t_orientation orientation;
} t_ray;

typedef struct s_drawing {
  int lineHeight;
  int drawStart;
  int drawEnd;
  double wallX;
  int texX;
} t_drawing;

// curTime: time of current frame
// prevTime: time of previous frame
typedef struct s_frame {
  double curTime;
  double prevTime;
} t_frame;

void set_dir(t_player *p, double dirX, double dirY) {
  p->dirX = dirX;
  p->dirY = dirY;
}

void set_plane(t_player *p, double planeX, double planeY) {
  p->planeX = planeX;
  p->planeY = planeY;
}

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

// cameraX: x coordinate on plane that represents current x on window (left =
// -1, middle = 0, right = 1) adding player dir vector and plane vector adjusted
// for cameraX results in vector of the ray
void generate_ray(int x, t_ray *r, t_player *p) {
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
void calc_initial_side_dist(t_ray *r, t_player p) {
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
void jump_to_next_square(t_ray *r, int **map) {
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

int main() {
  int **map;
  t_player_init i;
  t_player p;
  t_ray r;
  t_drawing d;
  int x;
  int y;

  while (1) {

    // raycasting loops over every x of the screen -> one calculation per column
    int x = 0;
    while (x < WIN_WIDTH) {
      generate_ray(x, &r, &p);
      calc_delta_dist(&r);
      calc_initial_side_dist(&r, p);
      jump_to_next_square(&r, map);
      calc_line_to_draw(&r, &d);
      calc_texture_x(r, p, &d);

      // TODO: Now loop over all y's to put the right pixel, ask Victor how to
      // extract pixel from texture


      x++;
    }
  }
  return 0;
}
