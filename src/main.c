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

void	prep_window(t_data *data) {
 data->d.x = 0;
  while (data->d.x < WIN_WIDTH) {
    calc_ray(data->d.x, &data->r, &data->p);
    calc_delta_dist(&data->r);
    calc_side_dist(&data->r, data->p);
    perform_dda(&data->r, data->map);
    calc_line_to_draw(&data->r, &data->d);
    calc_texture_x(data->r, data->p, &data->d);
    draw_line(data->d, data->r, &data->m);
    draw_ceiling_floor(data->d, &data->m);

    data->d.x++;
  }
  mlx_put_image_to_window(data->m.mlx_ptr, data->m.win_ptr, data->m.img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == K_ESC)
		close_window(&data->m);
	else if (keycode == K_W)
		move_w(&data->p, data->map);
	else if (keycode == K_A)
		move_a(&data->p, data->map);
	else if (keycode == K_S)
		move_s(&data->p, data->map);
	else if (keycode == K_D)
		move_d(&data->p, data->map);
	else if (keycode == K_LEFT)
		rot_left(&data->p);
	else if (keycode == K_RIGHT)
		rot_right(&data->p);
	else
		printf("keycode [%i]\n", keycode);
  prep_window(data);
	return (0);
}

int	main(void)
{
	t_data data;

	if (data_init(&data.i, &data.map))
		printf("Map Error\n");
  player_init(&data.p, data.i);
  data.m.mlx_ptr = mlx_init();
  data.m.win_ptr = mlx_new_window(data.m.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "deez cubez");
  data.m.img = mlx_new_image(data.m.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
  data.m.addr =
      mlx_get_data_addr(data.m.img, &data.m.bits_per_pixel, &data.m.line_length, &data.m.endian);
	get_draw_info(&data.d, data.m.mlx_ptr);
  mlx_hook(data.m.win_ptr, 17, 0L, close_window, &data.m);
  mlx_key_hook(data.m.win_ptr, key_hook, &data);
  prep_window(&data);
   mlx_loop(data.m.mlx_ptr);
  return 0;
}
