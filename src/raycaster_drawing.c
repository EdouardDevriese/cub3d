/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_drawing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:08:16 by wdevries          #+#    #+#             */
/*   Updated: 2024/03/07 13:46:06 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *m, int x, int y, int color)
{
	char	*dst;

	dst = m->addr + (y * m->line_length + x * (m->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_from_image(t_mlx tex, int x, int y)
{
	char	*dst;

	dst = tex.addr + (y * tex.line_length + x * (tex.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_line(t_drawing d, t_ray r, t_mlx *m)
{
	d.step = 1.0 * TEX_HEIGHT / d.line_height;
	d.tex_pos = (d.draw_start - WIN_HEIGHT / 2 + d.line_height / 2) * d.step;
	d.y = d.draw_start;
	while (d.y < d.draw_end)
	{
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
	while (d.y < d.draw_start && d.y < WIN_HEIGHT / 2)
		my_mlx_pixel_put(m, d.x, (d.y)++, d.floor);
	d.y = d.draw_end;
	while (d.y < WIN_HEIGHT - 1)
		my_mlx_pixel_put(m, d.x, (d.y)++, d.ceiling);
}
