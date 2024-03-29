/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_prep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:09:29 by wdevries          #+#    #+#             */
/*   Updated: 2024/03/07 14:07:06 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// cameraX: x coordinate on plane that represents current x on window (left =
// -1, middle = 0, right = 1) adding player dir vector and plane vector adjusted
// for cameraX results in vector of the ray
void	calc_ray(int x, t_ray *r, t_player *p)
{
	r->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	r->raydir_x = p->dir_x + p->plane_x * r->camera_x;
	r->raydir_y = p->dir_y + p->plane_y * r->camera_x;
}

// deltaDistX: distance ray has to travel to go from one x-side of map square to
// the next deltaDistY: distance ray has to travel to go from one y-side of map
// square to the next
void	calc_delta_dist(t_ray *r)
{
	if (r->raydir_x == 0)
		r->deltadist_x = INFINITY;
	else
		r->deltadist_x = fabs(1 / r->raydir_x);
	if (r->raydir_y == 0)
		r->deltadist_y = INFINITY;
	else
		r->deltadist_y = fabs(1 / r->raydir_y);
}

// map: coordinates of square ray is currently in
// sideDistX: distance ray has to travel to first next x-side of map square
// sideDistY: distance ray has to travel to first next y-side of map square
// step: sets possible directions for jump to next square (next step)
void	calc_side_dist(t_ray *r, t_player p)
{
	r->map_x = (int)p.pos_x;
	r->map_y = (int)p.pos_y;
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->sidedist_x = (p.pos_x - r->map_x) * r->deltadist_x;
	}
	else
	{
		r->step_x = 1;
		r->sidedist_x = (r->map_x + 1.0 - p.pos_x) * r->deltadist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->sidedist_y = (p.pos_y - r->map_y) * r->deltadist_y;
	}
	else
	{
		r->step_y = 1;
		r->sidedist_y = (r->map_y + 1.0 - p.pos_y) * r->deltadist_y;
	}
}

//lineHeight, inverse of distance of the wall (perpWallDist)
//drawStart/drawEnd: highest and lowest pixels to fill with wall (End
//		- Start = lineHeight)
void	calc_line_to_draw(t_ray *r, t_drawing *d)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->sidedist_x - r->deltadist_x);
	else
		r->perp_wall_dist = (r->sidedist_y - r->deltadist_y);
	if (r->perp_wall_dist == 0)
		d->line_height = INFINITY;
	else
		d->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
	d->draw_start = -d->line_height / 2 + WIN_HEIGHT / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = d->line_height / 2 + WIN_HEIGHT / 2;
	if (d->draw_end >= WIN_HEIGHT)
		d->draw_end = WIN_HEIGHT - 1;
}

void	calc_texture_x(t_ray r, t_player p, t_drawing *d)
{
	if (r.side == 0)
		d->wall_x = p.pos_y + r.perp_wall_dist * r.raydir_y;
	else
		d->wall_x = p.pos_x + r.perp_wall_dist * r.raydir_x;
	d->wall_x -= floor(d->wall_x);
	d->tex_x = (int)((double)TEX_WIDTH - d->wall_x * (double)TEX_WIDTH);
	if (r.side == 0 && r.raydir_x > 0)
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
	if (r.side == 1 && r.raydir_y < 0)
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
}
