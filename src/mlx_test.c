#define WIN_WIDTH 640
#define WIN_HEIGHT 480

#include <stdio.h>
#include "../minilibx-linux/mlx.h"

typedef struct s_mlx {
  void *mlx_ptr;
  void *win_ptr;
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
} t_mlx;

int	key_hook(int keycode, t_mlx *mlx)
{
	printf("You pressed a key: %i", keycode);
	return (0);
}

int main()
{
	t_mlx m;

	m.mlx_ptr = mlx_init();
	m.win_ptr = mlx_new_window(m.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "deez cubez");
	m.img = mlx_new_image(m.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	m.addr =
		mlx_get_data_addr(m.img, &m.bits_per_pixel, &m.line_length, &m.endian);
	mlx_key_hook(m.win_ptr, key_hook, &m);
	mlx_loop(m.mlx_ptr);
}
