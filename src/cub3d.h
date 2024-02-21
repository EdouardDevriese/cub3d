#ifndef CUB3D_H
# define CUB3D_H

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_MID 240
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#include <math.h>
#include <cstdint>

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
  int x;
  int y;
  int lineHeight;
  int drawStart;
  int drawEnd;
  double wallX;
  int texX;
  int texY;
  double texPos;
  double step;
  int32_t color;
} t_drawing;

// curTime: time of current frame
// prevTime: time of previous frame
typedef struct s_frame {
  double curTime;
  double prevTime;
} t_frame;


void player_init(t_player *p, t_player_init i);
void calc_ray(int x, t_ray *r, t_player *p);
void calc_delta_dist(t_ray *r);
void calc_side_dist(t_ray *r, t_player p);
void perform_dda(t_ray *r, int **map);
void calc_line_to_draw(t_ray *r, t_drawing *d);
void calc_texture_x(t_ray r, t_player p, t_drawing *d);

#endif
