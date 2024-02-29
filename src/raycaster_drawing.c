#include "cub3d.h"

// wallX: exact location of where ray hits the wall
// texX: x-coordinate of texture we want to draw, based on wallX
void	calc_texture_x(t_ray r, t_player p, t_drawing *d)
{
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

void	my_mlx_pixel_put(t_mlx *m, int x, int y, int color)
{
	char	*dst;

	dst = m->addr + (y * m->line_length + x * (m->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_pixel_from_image(t_mlx tex, int x, int y)
{
	char	*dst;

	dst = tex.addr + (y * tex.line_length + x * (tex.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void draw_line(t_drawing d, t_ray r, t_mlx *m) {
  d.step = 1.0 * TEX_HEIGHT / d.lineHeight;
  d.texPos = (d.drawStart - WIN_MID + d.lineHeight / 2) * d.step;
  d.y = d.drawStart;
  while (d.y < d.drawEnd) {
    d.texY = (int)d.texPos & (TEX_HEIGHT - 1);
    d.texPos += d.step;
    d.pixel = get_pixel_from_image(d.tex[r.orientation], d.texX, d.texY);
    my_mlx_pixel_put(m, d.x, d.y, d.pixel);
    d.y++;
  }
}

void	draw_ceiling_floor(t_drawing d, t_mlx *m)
{
	d.y = 0;
	while (d.y < d.drawStart && d.y < WIN_MID)
        my_mlx_pixel_put(m, d.x, (d.y)++, d.floor);
	d.y = d.drawEnd;
	while (d.y < WIN_HEIGHT)
        my_mlx_pixel_put(m, d.x, (d.y)++, d.ceiling);
}
