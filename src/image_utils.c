/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:26 by vdenisse          #+#    #+#             */
/*   Updated: 2024/03/07 09:59:10 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	check_info(t_check check)
{
	if (!check.no)
		return (1);
	if (!check.so)
		return (1);
	if (!check.ea)
		return (1);
	if (!check.we)
		return (1);
	if (!check.f)
		return (1);
	if (!check.c)
		return (1);
	return (0);
}

void	mlx_to_tex(t_drawing *d, void *mlx)
{
	d->tex[NO].mlx_ptr = mlx;
	d->tex[SO].mlx_ptr = mlx;
	d->tex[EA].mlx_ptr = mlx;
	d->tex[WE].mlx_ptr = mlx;
}

t_check	check_init(void)
{
	t_check	check;

	check.no = false;
	check.so = false;
	check.ea = false;
	check.we = false;
	check.c = false;
	check.f = false;
	return (check);
}

void	set_drawing_to_null(t_drawing *d)
{
	d->tex[NO].img = 0;
	d->tex[SO].img = 0;
	d->tex[WE].img = 0;
	d->tex[EA].img = 0;
}
