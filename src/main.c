#include "cub3d.h"
#include <stdint.h>

int	close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
}

int	key_hook(int keycode, t_hook_data *h)
{
	if (keycode == 65307)
		close_window(h->m);
	else if (keycode == 'w' || keycode == 65362)
		move_w(h->p, h->map);
	else if (keycode == 'a' || keycode == 65361)
		move_a(h->p, h->map);
	else if (keycode == 's' || keycode == 65364)
		move_s(h->p, h->map);
	else if (keycode == 'd' || keycode == 65363)
		move_d(h->p, h->map);
	else
		printf("keycode [%i]\n", keycode);
	return (0);
}


int	main(void)
{
	char			**map;
	t_player_init	i;
	t_player		p;
	t_ray			r;
	t_drawing		d;
	t_mlx			m;
	t_hook_data		h;

	data_init(&i, &map);
  player_init(&p, i);
  m.mlx_ptr = mlx_init();
  m.win_ptr = mlx_new_window(m.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "deez cubez");
  m.img = mlx_new_image(m.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
  m.addr =
      mlx_get_data_addr(m.img, &m.bits_per_pixel, &m.line_length, &m.endian);
// put iomages here
	get_draw_info(&d, m.mlx_ptr);
  mlx_hook(m.win_ptr, 17, 0L, close_window, &m);
	h.m = &m;
	h.p = &p;
	h.map = map;
  mlx_key_hook(m.win_ptr, key_hook, &h);

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
