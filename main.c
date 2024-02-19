#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#include <math.h>

typedef enum e_orientation { NO, SO, WE, EA } t_orientation;

typedef struct s_player {
  double posY;
  double posX;
  double dirY;
  double dirX;
  double planeX;
  double planeY;
} t_player;

typedef struct s_frame {
  double curTime;
  double prevTime;
} t_frame;

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

int main() {
  int map[10][10] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 1, 1, 0, 0, 1, 1, 0, 1}, {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 1, 1, 0, 0, 1, 1, 0, 1}, {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  t_player p;
  t_frame f;
  t_ray r;
  t_drawing d;
  int x;
  int y;

  p.posX = 5;
  p.posY = 5;
  p.dirX = -1;
  p.dirY = 0;
  p.planeX = 0;
  p.planeY = 0.66;

  f.curTime = 0;
  f.prevTime = 0;

  while (1) {
    // for every x in the screenwidht, so 640 columns
    int x = 0;
    while (x < WIN_WIDTH) {
      // generate rays
      r.cameraX = 2 * x / (double)WIN_WIDTH - 1;
      r.rayDirX = p.dirX + p.planeX * r.cameraX;
      r.rayDirY = p.dirY + p.planeY * r.cameraX;

      r.mapX = (int)p.posX;
      r.mapY = (int)p.posY;

      if (r.rayDirX == 0) {
        r.deltaDistX = INFINITY;
      } else {
        r.deltaDistX = fabs(1 / r.rayDirX);
      }
      if (r.rayDirY == 0) {
        r.deltaDistY = INFINITY;
      } else {
        r.deltaDistY = fabs(1 / r.rayDirY);
      }

      if (r.rayDirX < 0) {
        r.stepX = -1;
        r.sideDistX = (p.posX - r.mapX) * r.deltaDistX;
      } else {
        r.stepX = 1;
        r.sideDistX = (r.mapX + 1.0 - p.posX) * r.deltaDistX;
      }
      if (r.rayDirY < 0) {
        r.stepY = -1;
        r.sideDistY = (p.posY - r.mapY) * r.deltaDistY;
      } else {
        r.stepY = 1;
        r.sideDistY = (r.mapY + 1.0 - p.posY) * r.deltaDistY;
      }

      // perform DDA
      while (r.hit == 0) {
        // jump to next map square, either in x-direction, or in y-direction
        if (r.sideDistX < r.sideDistY) {
          r.sideDistX += r.deltaDistX;
          r.mapX += r.stepX;
          r.side = 0;
          if (r.rayDirX > 0)
            r.orientation = WE;
          else
            r.orientation = EA;
        } else {
          r.sideDistY += r.deltaDistY;
          r.mapY += r.stepY;
          r.side = 1;
          if (r.rayDirY > 0)
            r.orientation = SO;
          else
            r.orientation = NO;
        }
        // Check if ray has hit a wall
        if (map[r.mapX][r.mapY] > 0)
          r.hit = 1;
      }

      if (r.side == 0)
        r.perpWallDist = (r.sideDistX - r.deltaDistX);
      else
        r.perpWallDist = (r.sideDistY - r.deltaDistY);

      // Calculate height of line to draw on screen
      d.lineHeight = (int)(WIN_HEIGHT / r.perpWallDist);

      // calculate lowest and highest pixel to fill in current stripe
      d.drawStart = -d.lineHeight / 2 + WIN_HEIGHT / 2;
      if (d.drawStart < 0)
        d.drawStart = 0;
      d.drawEnd = d.lineHeight / 2 + WIN_HEIGHT / 2;
      if (d.drawEnd >= WIN_HEIGHT)
        d.drawEnd = WIN_HEIGHT - 1;

      if (r.side == 0)
        d.wallX = p.posY + r.perpWallDist * r.rayDirY;
      else
        d.wallX = p.posX + r.perpWallDist * r.rayDirX;
      d.wallX -= floor(d.wallX);

      // x coordinate on the texture
      d.texX = (int)(d.wallX * (double)TEX_WIDTH);
      if (r.side == 0 && r.rayDirX > 0)
        d.texX = TEX_WIDTH - d.texX - 1;
      if (r.side == 1 && r.rayDirY < 0)
        d.texX = TEX_WIDTH - d.texX - 1;

      // TODO: Now loop over all y's to put the right pixel, ask Victor how to extract pixel from texture

      x++;
    }
  }
  return 0;
}
