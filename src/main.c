#include "cub3d.h"


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
