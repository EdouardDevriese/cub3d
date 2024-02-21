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
    d.x = 0;
    while (d.x < WIN_WIDTH) {
      calc_ray(x, &r, &p);
      calc_delta_dist(&r);
      calc_side_dist(&r, p);
      perform_dda(&r, map);
      calc_line_to_draw(&r, &d);
      calc_texture_x(r, p, &d);

      // TODO: Now loop over all y's to put the right pixel, ask Victor how to
      // extract pixel from texture


      d.x++;
    }
  }
  return 0;
}
