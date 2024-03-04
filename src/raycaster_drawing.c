#include "cub3d.h"

// wallX: exact location of where ray hits the wall
// texX: x-coordinate of texture we want to draw, based on wallX
void	calc_texture_x(t_ray r, t_player p, t_drawing *d)
{
	if (r.side == 0)
		d->wall_x = p.posY + r.perp_wall_dist * r.raydir_y;
	else
		d->wall_x = p.posX + r.perp_wall_dist * r.raydir_x;
	d->wall_x -= floor(d->wall_x);
	d->texX = (int)(d->wall_x * (double)TEX_WIDTH);
	if (r.side == 0 && r.raydir_x > 0)
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
	if (r.side == 1 && r.raydir_y < 0)
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
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
  d.step = 1.0 * TEX_HEIGHT / d.line_height;
  d.texPos = (d.drawStart - WIN_MID + d.line_height / 2) * d.step;
  d.y = d.draw_start;
  while (d.y < d.draw_end) {
    d.tex_y = (int)d.tex_pos & (TEX_HEIGHT - 1);
    d.tex_pos += d.step;
    d.pixel = get_pixel_from_image(d.tex[r.orientation], d.tex_x, d.tex_y);
    my_mlx_pixel_put(m, d.x, d.y, d.pixel);
    d.y++;
  }
}

void	draw_ceiling_floor(t_drawing d, t_mlx *m)
{
	d.y = 0;
	while (d.y < d.draw_start && d.y < WIN_MID)
        my_mlx_pixel_put(m, d.x, (d.y)++, d.floor);
	d.y = d.draw_end;
	while (d.y < WIN_HEIGHT)
        my_mlx_pixel_put(m, d.x, (d.y)++, d.ceiling);
}
