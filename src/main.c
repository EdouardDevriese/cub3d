#include "cub3d.h"
#include <stdint.h>

int ft_close_window(t_mlx *mlx) {
  mlx_destroy_image(mlx->mlx_ptr, mlx->img);
  mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
  mlx_destroy_display(mlx->mlx_ptr);
  free(mlx->mlx_ptr);
  exit(0);
}

int ft_escape(int keycode, t_mlx *mlx) {
  if (keycode == 65307)
    ft_close_window(mlx);
  return (0);
}

int32_t rgb_to_int(int r, int g, int b) {
  return ((r << 16) | (g << 8) | b);
}

int main() {
  char **map;
  t_player_init i;
  t_player p;
  t_ray r;
  t_drawing d;
  t_mlx m;

  //@victor
  // fill in t_player_init i, pass it to player_init.
  // fill in textures in t_drawing void *tex[4]
	data_init(&i, &map);
  player_init(&p, i);
  m.mlx_ptr = mlx_init();
  m.win_ptr = mlx_new_window(m.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "deez cubez");
  m.img = mlx_new_image(m.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
  m.addr =
      mlx_get_data_addr(m.img, &m.bits_per_pixel, &m.line_length, &m.endian);
  mlx_hook(m.win_ptr, 17, 0L, ft_close_window, &m);
  mlx_key_hook(m.win_ptr, ft_escape, &m);

  d.x = 0;
  while (d.x < WIN_WIDTH) {
    calc_ray(d.x, &r, &p);
    calc_delta_dist(&r);
    calc_side_dist(&r, p);
    perform_dda(&r, map);
    calc_line_to_draw(&r, &d);
    calc_texture_x(r, p, &d);
    draw_line(d, r, m);
    draw_ceiling_floor(d, m);

    d.x++;
  }
  mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.img, 0, 0);
  mlx_loop(m.mlx_ptr);
  return 0;
}
